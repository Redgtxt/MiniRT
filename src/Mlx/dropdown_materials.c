/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dropdown_materials.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 11:27:03 by hguerrei          #+#    #+#             */
/*   Updated: 2025/07/16 17:13:57 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void init_material_selector(t_material_selector *selector)
{
    selector->x = 50;
    selector->y = 350;
    selector->width = 150;
    selector->height = 30;
    selector->dropdown_height = 150; // 5 materiais * 30px cada
    selector->is_open = 0;
    selector->selected_material = LAMBERTIAN;
    selector->hover_index = -1;
    selector->item_height = 30;
    selector->color_button = COLOR_GRAY;
    selector->color_dropdown = COLOR_DARK_GRAY;
    selector->color_hover = COLOR_BLUE;
    selector->color_text = COLOR_WHITE;

    // Inicializar nomes dos materiais
    selector->material_names[0] = "LAMBERTIAN";
    selector->material_names[1] = "METAL";
    selector->material_names[2] = "CHECKER";
    selector->material_names[3] = "SOLID";
    selector->material_names[4] = "GLASS";
}

// Desenhar o material selector
void draw_material_selector(t_control_panel *cp)
{
    t_material_selector *selector = &cp->config_win->material_selector;

    // Desenhar botão principal
    draw_rectangle(cp, selector->x, selector->y, selector->width, selector->height, selector->color_button);
    draw_text(cp, selector->x + 10, selector->y + 10, selector->material_names[selector->selected_material], selector->color_text);

    // Desenhar seta para baixo
    draw_arrow_down(cp, selector->x + selector->width - 20, selector->y + 10);

    // Se estiver aberto, desenhar dropdown
    if (selector->is_open)
    {
        int dropdown_y = selector->y + selector->height;

        // Desenhar fundo do dropdown
        draw_rectangle(cp, selector->x, dropdown_y, selector->width, selector->dropdown_height, selector->color_dropdown);

        // Desenhar cada item do material
        for (int i = 0; i < 5; i++) // Atualizado para 5 materiais
        {
            int item_y = dropdown_y + (i * selector->item_height);
            int item_color = selector->color_dropdown;

            // Destacar item em hover
            if (i == selector->hover_index)
                item_color = selector->color_hover;

            // Destacar item selecionado
            if (i == selector->selected_material)
                item_color = selector->color_hover;

            draw_rectangle(cp, selector->x, item_y, selector->width, selector->item_height, item_color);
            draw_text(cp, selector->x + 10, item_y + 10, selector->material_names[i], selector->color_text);
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

void draw_arrow_down(t_control_panel *cp, int x, int y)
{
    // Desenhar uma seta simples para baixo
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            pixel_put_win_control(cp, x + 2 + j, y + i, COLOR_WHITE);
            pixel_put_win_control(cp, x + 2 - j, y + i, COLOR_WHITE);
        }
    }
}
