#include "../../includes/miniRT.h"

static int get_rgb_component_index(t_control_panel *cp, t_slider *slider)
{
    if (slider == &cp->config_win->red_slider)
        return (0);
    else if (slider == &cp->config_win->green_slider)
        return (1);
    else if (slider == &cp->config_win->blue_slider)
        return (2);
    return (-1);
}

void handle_rgb_slider_interaction(t_control_panel *cp, t_slider *slider,
                                   int x, int y)
{
    int rgb_index;
    int interaction_result;

    if (!cp || !slider)
        return;
    rgb_index = get_rgb_component_index(cp, slider);
    if (rgb_index == -1)
        return;
    interaction_result = handle_slider_interaction(slider, x, y);
    if (interaction_result > 0)
    {
        update_object_rgb(cp, rgb_index, slider->current_value);
        redraw_interface(cp);
    }
}