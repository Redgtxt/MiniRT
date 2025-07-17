#include "../../includes/miniRT.h"

static int find_clicked_object(t_control_panel *cp, int mouse_x, int mouse_y, int *obj_type)
{
    t_ray ray;
    t_hit_record record;
    t_interval t_ray;

    // Criar um raio a partir da posição do mouse
    ray = get_ray(mouse_x, mouse_y, cp);

    // Definir intervalo do raio
    t_ray = interval_create(0.001, D_INFINITY);

    // Usar sua função existente hit_world para encontrar o objeto mais próximo
    if (hit_world(cp, &ray, t_ray, &record))
    {
        // Verificar esferas
        for (size_t i = 0; i < cp->data.sphere_count; i++)
        {
            t_hit_record sphere_record;

            // Usar sua função have_hit_sphere para testar esta esfera específica
            if (have_hit_sphere(&cp->sphere[i], &ray, t_ray, &sphere_record))
            {
                // Verificar se é a esfera mais próxima (comparar distâncias)
                if (fabs(sphere_record.t - record.t) < 0.001)
                {
                    *obj_type = 0; // Tipo esfera
                    return (int)i; // Retornar índice da esfera
                }
            }
        }

        // Verificar planos
        for (size_t i = 0; i < cp->data.plane_count; i++)
        {
            t_hit_record plane_record;
            // Verificar se este plano foi atingido
            if (have_hit_plane(&cp->plane[i], &ray, t_ray, &plane_record))
            {
                // Verificar se é o plano mais próximo (comparar distâncias)
                if (fabs(plane_record.t - record.t) < 0.001)
                {
                    *obj_type = 1; // Tipo plano
                    return (int)i; // Retornar índice do plano
                }
            }
        }

        // Verificar cilindros
        for (size_t i = 0; i < cp->data.cylinder_count; i++)
        {
            t_hit_record cylinder_record;
            // Verificar se este cilindro foi atingido
            if (have_hit_cylinder(&cp->cylinder[i], &ray, t_ray, &cylinder_record))
            {
                // Verificar se é o cilindro mais próximo (comparar distâncias)
                if (fabs(cylinder_record.t - record.t) < 0.001)
                {
                    *obj_type = 2; // Tipo cilindro
                    return (int)i; // Retornar índice do cilindro
                }
            }
        }

        for (size_t i = 0; i < cp->data.cone_count; i++)
        {
            t_hit_record cone_record;
            // Verificar se este cilindro foi atingido
            if (have_hit_cone(&cp->cone[i], &ray, t_ray, &cone_record))
            {
                // Verificar se é o cilindro mais próximo (comparar distâncias)
                if (fabs(cone_record.t - record.t) < 0.001)
                {
                    *obj_type = 3; // Tipo cilindro
                    return (int)i; // Retornar índice do cilindro
                }
            }
        }
    }

    return -1; // Nenhum objeto encontrado
}

// Função para atualizar a interface de controle com o objeto selecionado
static void update_control_interface_with_object(t_control_panel *cp, int obj_index, int obj_type)
{
    cp->data.idx_obj = obj_index;
    cp->data.obj_type = obj_type;

    // Atualizar os valores dos sliders RGB com base no tipo de objeto
    switch (obj_type)
    {
    case 0: // Esfera
        if (obj_index >= 0 && obj_index < (int)cp->data.sphere_count)
        {
            t_sphere *selected = &cp->sphere[obj_index];
            cp->config_win->red_slider.current_value = selected->rgb[0];
            cp->config_win->green_slider.current_value = selected->rgb[1];
            cp->config_win->blue_slider.current_value = selected->rgb[2];

            // Add this line to update the material selector
            cp->config_win->material_selector.selected_material = selected->material.type;

            printf("Esfera %d selecionada! RGB: %.2f, %.2f, %.2f\n",
                   obj_index, selected->rgb[0], selected->rgb[1], selected->rgb[2]);
        }
        break;

    case 1: // Plano
        if (obj_index >= 0 && obj_index < (int)cp->data.plane_count)
        {
            t_plane *selected = &cp->plane[obj_index];
            cp->config_win->red_slider.current_value = selected->rgb[0];
            cp->config_win->green_slider.current_value = selected->rgb[1];
            cp->config_win->blue_slider.current_value = selected->rgb[2];

            // Add this line to update the material selector
            cp->config_win->material_selector.selected_material = selected->material.type;

            printf("Plano %d selecionado! RGB: %.2f, %.2f, %.2f\n",
                   obj_index, selected->rgb[0], selected->rgb[1], selected->rgb[2]);
        }
        break;

    case 2: // Cilindro
        if (obj_index >= 0 && obj_index < (int)cp->data.cylinder_count)
        {
            t_cylinder *selected = &cp->cylinder[obj_index];
            cp->config_win->red_slider.current_value = selected->rgb[0];
            cp->config_win->green_slider.current_value = selected->rgb[1];
            cp->config_win->blue_slider.current_value = selected->rgb[2];

            // Add this line to update the material selector
            cp->config_win->material_selector.selected_material = selected->material.type;

            printf("Cilindro %d selecionado! RGB: %.2f, %.2f, %.2f\n",
                   obj_index, selected->rgb[0], selected->rgb[1], selected->rgb[2]);
        }
        break;
    case 3: // Cone
        if (obj_index >= 0 && obj_index < (int)cp->data.cone_count)
        {
            t_cone *selected = &cp->cone[obj_index];
            cp->config_win->red_slider.current_value = selected->rgb[0];
            cp->config_win->green_slider.current_value = selected->rgb[1];
            cp->config_win->blue_slider.current_value = selected->rgb[2];

            // Add this line to update the material selector
            cp->config_win->material_selector.selected_material = selected->material.type;

            printf("Cone %d selecionado! RGB: %.2f, %.2f, %.2f\n",
                   obj_index, selected->rgb[0], selected->rgb[1], selected->rgb[2]);
        }
        break;
    }

    // Redesenhar a interface de controle
    redraw_interface(cp);
}

int main_window_mouse_handler(int button, int x, int y, void *param)
{
    t_control_panel *cp = (t_control_panel *)param;
    int clicked_object;
    int obj_type = 0;

    if (button == 1) // Left button
    {
        clicked_object = find_clicked_object(cp, x, y, &obj_type);

        if (clicked_object >= 0)
        {
            update_control_interface_with_object(cp, clicked_object, obj_type);
        }
        else
        {
            printf("No object clicked at position (%d, %d)\n", x, y);
        }
    }

    return (0);
}