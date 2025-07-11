#include "../../includes/miniRT.h"

static void handle_dragging_rgb_slider(t_control_panel *cp)
{
    // Check if any valid object type is selected
    bool valid_object = (cp->data.obj_type == 0 && cp->data.idx_obj >= 0 && cp->data.idx_obj < (int)cp->data.sphere_count) ||
                        (cp->data.obj_type == 1 && cp->data.idx_obj >= 0 && cp->data.idx_obj < (int)cp->data.plane_count) ||
                        (cp->data.obj_type == 2 && cp->data.idx_obj >= 0 && cp->data.idx_obj < (int)cp->data.cylinder_count);

    if (valid_object)
    {
        if (cp->config_win->red_slider.is_dragging)
        {
            cp->config_win->red_slider.is_dragging = 0;
            printf("Slider RED solto! \n");
        }

        if (cp->config_win->green_slider.is_dragging)
        {
            cp->config_win->green_slider.is_dragging = 0;
            printf("Slider GREEN solto! \n");
        }

        if (cp->config_win->blue_slider.is_dragging)
        {
            cp->config_win->blue_slider.is_dragging = 0;
            printf("Slider BLUE solto! \n");
        }
    }
}

int mouse_release_handler(int button, int x, int y, void *param)
{
    (void)x;
    (void)y;
    t_control_panel *cp;
    t_slider *slider;

    cp = (t_control_panel *)param;

    if (!cp || !cp->config_win)
        return (0);

    slider = &cp->config_win->slider;

    if (button == 1) // Botão esquerdo solto
    {
        // Slider amb light
        if (slider->is_dragging)
        {
            slider->is_dragging = 0;
            printf("Slider principal solto!\n");
        }
        // Sliders RGB
        handle_dragging_rgb_slider(cp);
    }

    return (0);
}
