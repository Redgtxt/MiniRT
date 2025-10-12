/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_panel.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 00:00:00 by ruigoncalve      #+#    #+#             */
/*   Updated: 2025/10/03 00:00:00 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTROL_PANEL_H
# define CONTROL_PANEL_H

# include "../core/types.h"
# include "../graphics/camera.h"
# include "../graphics/lighting.h"
# include "../io/errors.h"
# include "../objects/cone.h"
# include "../objects/cylinder.h"
# include "../objects/plane.h"
# include "../objects/sphere.h"
# include "../system/mlx_wrapper.h"

/* Main control panel structure */
typedef struct s_cp
{
	t_amb_light		amb_light;
	t_camera		camera;
	t_light			*light;
	t_sphere		*sphere;
	t_plane			*plane;
	t_cylinder		*cylinder;
	t_cone			*cone;
	t_texture		*textures;
	void			*texture_list;
	t_data			data;
	t_error_log		error_log;
	t_mlx			*mlx;
	t_win_config	*config_win;
}					t_control_panel;

/* Testing and debugging functions */
void				print_elements(t_control_panel *control_panel);

#endif