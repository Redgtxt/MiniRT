#include "../../includes/miniRT.h"

void change_amb_light_brightness(int keycode, t_control_panel *control_panel)
{
    t_interval interval;

    interval = interval_create(0, 1);
    if (keycode == ARROW_UP_KEY)
    {
        control_panel->amb_light.light_force += .1;
        control_panel->amb_light.light_force = clamp(control_panel->amb_light.light_force, interval);
        printf(HMAG "Ambient brightness: %.1f " RESET, control_panel->amb_light.light_force);

        clear_image(control_panel);
        render_scene(control_panel);
    }
    if (keycode == ARROW_DOWN_KEY)
    {
        control_panel->amb_light.light_force -= .1;
        control_panel->amb_light.light_force = clamp(control_panel->amb_light.light_force, interval);
        printf(HMAG "Ambient brightness: %.1f " RESET, control_panel->amb_light.light_force);

        clear_image(control_panel);
        render_scene(control_panel);
    }
}
