/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dropdown_materials.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:27:03 by hguerrei          #+#    #+#             */
/*   Updated: 2025/07/22 18:50:30 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void init_material_selector(t_material_selector *selector)
{
    selector->x = 50;
    selector->y = 375;
    selector->width = 150;
    selector->height = 30;
    selector->dropdown_height = 150; // 5 materiais * 30px cada
    selector->is_open = 0;
    selector->selected_material = LAMBERTIAN;
    selector->hover_index = -1;
    selector->item_height = 30;
    // Cores melhoradas
    selector->color_button = COLOR_BUTTON_BG;
    selector->color_dropdown = COLOR_DROPDOWN_BG;
    selector->color_hover = COLOR_HOVER;
    selector->color_text = COLOR_TEXT_SOFT;

    // Inicializar nomes dos materiais
    selector->material_names[0] = "SOLID";
    selector->material_names[1] = "LAMBERTIAN";
    selector->material_names[2] = "METAL";
    selector->material_names[3] = "CHECKER";
    selector->material_names[4] = "GLASS";
}

// Desenhar o material selector
void draw_material_selector(t_control_panel *cp)
{
    t_material_selector *selector = &cp->config_win->material_selector;

    // Desenhar botão principal com borda
    draw_rectangle(cp, selector->x, selector->y, selector->width, selector->height, selector->color_button);
    draw_border(cp, selector->x, selector->y, selector->width, selector->height, COLOR_WHITE);

    draw_text(cp, selector->x + 10, selector->y + 20, selector->material_names[selector->selected_material], selector->color_text);

    // Desenhar seta melhorada
    draw_arrow_down(cp, selector->x + selector->width - 20, selector->y + 10);

    // Se estiver aberto, desenhar dropdown
    if (selector->is_open)
    {
        int dropdown_y = selector->y + selector->height;

        // Desenhar fundo do dropdown com borda
        draw_rectangle(cp, selector->x, dropdown_y, selector->width, selector->dropdown_height, selector->color_dropdown);
        draw_border(cp, selector->x, dropdown_y, selector->width, selector->dropdown_height, COLOR_WHITE);

        // Desenhar cada item do material
        for (int i = 0; i < 5; i++) // Atualizado para 5 materiais
        {
            int item_y = dropdown_y + (i * selector->item_height);
            int item_color = selector->color_dropdown;

            // Destacar item em hover
            if (i == selector->hover_index)
                item_color = COLOR_HOVER;

            // Destacar item selecionado
            if (i == selector->selected_material)
                item_color = COLOR_SELECTED;

            draw_rectangle(cp, selector->x + 2, item_y + 1, selector->width - 4, selector->item_height - 2, item_color);
            draw_text(cp, selector->x + 10, item_y + 20, selector->material_names[i], selector->color_text);
        }
    }
}

// Verificar se mouse está sobre o selector
int is_mouse_on_material_selector(t_material_selector *selector, int mouse_x, int mouse_y)
{
    // Verificar botão principal
    if (mouse_x >= selector->x && mouse_x <= selector->x + selector->width &&
        mouse_y >= selector->y && mouse_y <= selector->y + selector->height)
        return 1;

    // Se dropdown estiver aberto, verificar área do dropdown
    if (selector->is_open)
    {
        int dropdown_y = selector->y + selector->height;
        if (mouse_x >= selector->x && mouse_x <= selector->x + selector->width &&
            mouse_y >= dropdown_y && mouse_y <= dropdown_y + selector->dropdown_height)
            return 1;
    }

    return 0;
}

// Obter índice do item no dropdown baseado na posição do mouse
int get_dropdown_item_index(t_material_selector *selector, int mouse_x, int mouse_y)
{
    if (!selector->is_open)
        return -1;

    int dropdown_y = selector->y + selector->height;

    if (mouse_x >= selector->x && mouse_x <= selector->x + selector->width &&
        mouse_y >= dropdown_y && mouse_y <= dropdown_y + selector->dropdown_height)
    {
        int relative_y = mouse_y - dropdown_y;
        int index = relative_y / selector->item_height;

        if (index >= 0 && index < 5) // Atualizado para 4 materiais
            return index;
    }

    return -1;
}

// Lidar com clique no material selector
void handle_material_selector_click(t_control_panel *cp, int mouse_x, int mouse_y)
{
    t_material_selector *selector = &cp->config_win->material_selector;

    // Clique no botão principal
    if (mouse_x >= selector->x && mouse_x <= selector->x + selector->width &&
        mouse_y >= selector->y && mouse_y <= selector->y + selector->height)
    {
        selector->is_open = !selector->is_open;
        selector->hover_index = -1;
        return;
    }

    // Clique no dropdown (se estiver aberto)
    if (selector->is_open)
    {
        int item_index = get_dropdown_item_index(selector, mouse_x, mouse_y);
        if (item_index >= 0)
        {
            selector->selected_material = item_index;
            selector->is_open = 0;
            selector->hover_index = -1;
        }
        else
        {
            // Clique fora do dropdown, fechar
            selector->is_open = 0;
            selector->hover_index = -1;
        }
    }
}

// Lidar com movimento do mouse
void handle_material_selector_hover(t_control_panel *cp, int mouse_x, int mouse_y)
{
    t_material_selector *selector = &cp->config_win->material_selector;

    if (selector->is_open)
    {
        int item_index = get_dropdown_item_index(selector, mouse_x, mouse_y);
        selector->hover_index = item_index;
    }
}

// Aplicar material ao objeto selecionado
void apply_material_to_selected_object(t_control_panel *cp, t_material_type material_type)
{
    t_data *data = &cp->data;

    // Só altera o objeto atualmente selecionado!
    if (data->obj_type == 0 && data->idx_obj >= 0 && data->idx_obj < (int)data->sphere_count)
    {
        cp->sphere[data->idx_obj].material.type = material_type;
        configure_material_properties(&cp->sphere[data->idx_obj].material, material_type);
    }
    else if (data->obj_type == 1 && data->idx_obj >= 0 && data->idx_obj < (int)data->plane_count)
    {
        cp->plane[data->idx_obj].material.type = material_type;
        configure_material_properties(&cp->plane[data->idx_obj].material, material_type);
    }
    else if (data->obj_type == 2 && data->idx_obj >= 0 && data->idx_obj < (int)data->cylinder_count)
    {
        cp->cylinder[data->idx_obj].material.type = material_type;
        configure_material_properties(&cp->cylinder[data->idx_obj].material, material_type);
    }
    else if (data->obj_type == 3 && data->idx_obj >= 0 && data->idx_obj < (int)data->cone_count)
    {
        cp->cone[data->idx_obj].material.type = material_type;
        configure_material_properties(&cp->cone[data->idx_obj].material, material_type);
    }
}

// Configurar propriedades específicas do material
void configure_material_properties(t_material *material, t_material_type type)
{
    switch (type)
    {
    case SOLID:
        break;
    case LAMBERTIAN:
        material->shininess = 0.0;
        // Manter albedo atual
        break;

    case METAL:
        material->shininess = 50.0;
        // Configurar propriedades metálicas
        material->specular[0] = 0.8;
        material->specular[1] = 0.8;
        material->specular[2] = 0.8;
        break;
    case CHECKERPATTERN:
        material->shininess = 0.0;
        // Definir escala do padrão xadrez
        material->checker_scale = .5;
        // Manter albedo para a cor principal do xadrez
        break;

    case GLASS:
        material->shininess = 200.0;
        material->refraction_index = 1.5; // Glass refractive index
        // Configurar propriedades do vidro
        material->specular[0] = 1.0;
        material->specular[1] = 1.0;
        material->specular[2] = 1.0;
        break;

        // Adicionar outros materiais conforme necessário
    }
}

// Funções auxiliares para desenhar (implementar conforme teu sistema de desenho)
void draw_rectangle(t_control_panel *cp, int x, int y, int width, int height, int color)
{
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            pixel_put_win_control(cp, x + i, y + j, color);
        }
    }
}

void draw_text(t_control_panel *cp, int x, int y, char *text, int color)
{
    // Implementar desenho de texto simples
    // Podes usar a mlx_string_put ou implementar teu próprio sistema
    mlx_string_put(cp->config_win->mlx, cp->config_win->win, x, y, color, text);
}

// Adicionar função para desenhar bordas
void draw_border(t_control_panel *cp, int x, int y, int width, int height, int color)
{
    // Borda superior
    for (int i = 0; i < width; i++)
        pixel_put_win_control(cp, x + i, y, color);

    // Borda inferior
    for (int i = 0; i < width; i++)
        pixel_put_win_control(cp, x + i, y + height - 1, color);

    // Borda esquerda
    for (int i = 0; i < height; i++)
        pixel_put_win_control(cp, x, y + i, color);

    // Borda direita
    for (int i = 0; i < height; i++)
        pixel_put_win_control(cp, x + width - 1, y + i, color);
}

// Seta melhorada
void draw_arrow_down(t_control_panel *cp, int x, int y)
{
    // Desenhar triângulo mais definido
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j <= 6 - i; j++)
        {
            pixel_put_win_control(cp, x + 3 + j, y + i, COLOR_WHITE);
            pixel_put_win_control(cp, x + 3 - j, y + i, COLOR_WHITE);
        }
    }
}

// Botão melhorado
void draw_button(t_control_panel *cp, t_button button)
{
    // Fundo do botão com gradiente simples
    draw_rectangle(cp, button.x, button.y, button.width, button.height, 0x20A020);

    // Highlight no topo
    for (int i = 0; i < button.width; i++)
        pixel_put_win_control(cp, button.x + i, button.y, COLOR_HIGHLIGHT);

    // Sombra na base
    for (int i = 0; i < button.width; i++)
        pixel_put_win_control(cp, button.x + i, button.y + button.height - 1, COLOR_SHADOW);

    // Bordas laterais
    for (int i = 0; i < button.height; i++)
    {
        pixel_put_win_control(cp, button.x, button.y + i, COLOR_HIGHLIGHT);
        pixel_put_win_control(cp, button.x + button.width - 1, button.y + i, COLOR_SHADOW);
    }
}

// Barra do slider melhorada
void draw_slider_bar_improved(t_control_panel *cp, t_slider slider)
{
    // Fundo da barra (cor mais escura)
    draw_rectangle(cp, slider.x, slider.y, slider.width, slider.height, 0x202020);

    // Borda da barra
    draw_border(cp, slider.x, slider.y, slider.width, slider.height, COLOR_BORDER);

    // Parte preenchida (gradiente simples)
    float value_ratio = (slider.current_value - slider.min_value) / (slider.max_value - slider.min_value);
    int filled_width = (int)(slider.width * value_ratio);

    if (filled_width > 2)
        draw_rectangle(cp, slider.x + 1, slider.y + 1, filled_width - 2, slider.height - 2, slider.color_handle);
}

// Handle do slider melhorado
void draw_slider_handle_improved(t_control_panel *cp, int x, int y, int width, int height, int color)
{
    // Handle principal
    draw_rectangle(cp, x, y, width, height, color);

    // Borda do handle
    draw_border(cp, x, y, width, height, COLOR_WHITE);

    // Highlight no topo para efeito 3D
    for (int i = 1; i < width - 1; i++)
        pixel_put_win_control(cp, x + i, y + 1, COLOR_WHITE);
}
