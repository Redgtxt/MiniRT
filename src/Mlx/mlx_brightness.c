#include "../../includes/miniRT.h"

void change_object_brightness(int keycode, t_control_panel *control_panel)
{
    t_interval interval;

    interval = interval_create(0, 1);
    if (keycode == ARROW_LEFT_KEY)
    {
        control_panel->light.object_brightness -= .1;
        control_panel->light.object_brightness = clamp(control_panel->light.object_brightness, interval);
        printf(HMAG "Object brightness: %.1f " reset, control_panel->light.object_brightness);

        clear_image(control_panel);
        render_scene(control_panel);
    }
    if (keycode == ARROW_RIGHT_KEY)
    {

        control_panel->light.object_brightness += .1;
        control_panel->light.object_brightness = clamp(control_panel->light.object_brightness, interval);
        printf(HMAG "Object brightness: %.1f " reset, control_panel->light.object_brightness);

        clear_image(control_panel);
        render_scene(control_panel);
    }
}
