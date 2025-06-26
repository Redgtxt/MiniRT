#include "../../includes/miniRT.h"

static int find_clicked_object(t_control_panel *cp, int mouse_x, int mouse_y)
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
        // Agora precisamos descobrir qual esfera específica foi atingida
        // Vamos testar cada esfera individualmente
        for (size_t i = 0; i < cp->data.sphere_count; i++)
        {
            t_hit_record sphere_record;
            
            // Usar sua função have_hit_sphere para testar esta esfera específica
            if (have_hit_sphere(&cp->sphere[i], &ray, t_ray, &sphere_record))
            {
                // Verificar se é a esfera mais próxima (comparar distâncias)
                if (fabs(sphere_record.t - record.t) < 0.001)
                {
                    return (int)i;  // Retornar índice da esfera
                }
            }
        }
    }
    
    return -1; // Nenhum objeto encontrado
}

// Função para atualizar a interface de controle com o objeto selecionado
static void update_control_interface_with_object(t_control_panel *cp, int obj_index)
{
    if (obj_index < 0 || obj_index >= (int)cp->data.sphere_count)
        return;
    
    // Atualizar o índice atual
    cp->data.idx_obj = obj_index;
    
    t_sphere *selected_sphere = &cp->sphere[obj_index];
    
    // Atualizar os valores dos sliders RGB
    cp->config_win->red_slider.current_value = selected_sphere->rgb[0];
    cp->config_win->green_slider.current_value = selected_sphere->rgb[1];
    cp->config_win->blue_slider.current_value = selected_sphere->rgb[2];
    
    // Redesenhar a interface de controle
    redraw_interface(cp);
    
    printf("Object %d selected! RGB: %.2f, %.2f, %.2f\n", 
           obj_index, selected_sphere->rgb[0], selected_sphere->rgb[1], selected_sphere->rgb[2]);
}

int main_window_mouse_handler(int button, int x, int y, void *param)
{
    t_control_panel *cp = (t_control_panel *)param;
    int clicked_object;
    
    if (button == 1) // Botão esquerdo
    {
        clicked_object = find_clicked_object(cp, x, y);
        
        if (clicked_object >= 0)
        {
            update_control_interface_with_object(cp, clicked_object);
        }
        else
        {
            printf("No object clicked at position (%d, %d)\n", x, y);
        }
    }
    
    return (0);
}