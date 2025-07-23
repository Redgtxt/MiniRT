#include "../../includes/miniRT.h"

void pixel_put_win_control(t_control_panel *cp, int x, int y, int color)
{
    char *dst;
    t_win_config *control_data;
    t_interval x_interval;
    t_interval y_interval;

    control_data = cp->config_win;
    if (!control_data)
        return;

    x_interval = interval_create(0, W_WIDTH - 1);
    y_interval = interval_create(0, W_HEIGHT - 1);

    if (interval_contains(x, x_interval) && interval_contains(y, y_interval))
    {
        dst = control_data->addr + (y * control_data->line_length + x * (control_data->bits_per_pixel / 8));
        *(unsigned int *)dst = color;
    }
}

int	render_button(t_control_panel *cp, t_slider *slider, int x, int y)
{
	t_interval		x_interval;
	t_interval		y_interval;
	t_button		btn;

	btn = cp->config_win->button;
	x_interval = interval_create(btn.x, btn.x + btn.width);
	y_interval = interval_create(btn.y, btn.y + btn.height);
	if (interval_contains(x, x_interval) && interval_contains(y, y_interval))
	{
	    update_objects_properties(cp,slider);
		return (1);
	}
	return (0);
}