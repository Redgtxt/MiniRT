/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sliders_from_selected_object.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:54:46 by hguerrei          #+#    #+#             */
/*   Updated: 2025/07/24 16:54:53 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"


static char	*get_object_name(int obj_type)
{
    if (obj_type == 0)
        return ("Sphere");
    else if (obj_type == 1)
        return ("Plane");
    else if (obj_type == 2)
        return ("Cylinder");
    else if (obj_type == 3)
        return ("Cone");
    return ("Object");
}

static void	set_sliders_and_redraw(t_control_panel *cp, double r,
        double g, double b)
{
    char	*obj_name;

    cp->config_win->red_slider.current_value = r;
    cp->config_win->green_slider.current_value = g;
    cp->config_win->blue_slider.current_value = b;
    redraw_interface(cp);
    obj_name = get_object_name(cp->data.obj_type);
    printf("🔄 %s %d selecionado - RGB: %.2f, %.2f, %.2f\n",
        obj_name, cp->data.idx_obj, r, g, b);
}


void	update_sliders_from_selected_object(t_control_panel *cp)
{
    double	r;
    double	g;
    double	b;
    int		valid_object;

    r = 0;
    g = 0;
    b = 0;
    valid_object = 0;
    valid_object = get_rgb_values(cp, &r, &g, &b);
    if (valid_object)
          set_sliders_and_redraw(cp, r, g, b);
}
