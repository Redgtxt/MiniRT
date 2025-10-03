/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:40:49 by randrade          #+#    #+#             */
/*   Updated: 2025/10/03 14:02:43 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

/* Standard C libraries */
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <float.h>
# include <fcntl.h>
# include <errno.h>
# include <unistd.h>
# include <time.h>

/* External libraries */
# include "../Library/ft_printf/ft_printf.h"
# include "../Library/get_next_line/get_next_line.h"
# include "../Library/libft/libft.h"
# include "../Library/minilibx-linux/mlx.h"

/* Core includes */
# include "core/constants.h"
# include "core/types.h"

/* Math includes */
# include "math/vec3.h"
# include "math/interval.h"

/* Graphics includes */
# include "graphics/ray.h"
# include "graphics/materials.h"
# include "graphics/camera.h"
# include "graphics/lighting.h"
# include "graphics/render.h"

/* Object includes */
# include "objects/objects.h"
# include "objects/sphere.h"
# include "objects/plane.h"
# include "objects/cylinder.h"
# include "objects/cone.h"

/* System includes */
# include "system/mlx_wrapper.h"
# include "system/memory.h"

/* UI includes */
# include "ui/ui.h"

/* I/O includes */
# include "io/errors.h"
# include "io/parsing.h"

/* Main control panel */
# include "core/control_panel.h"

#endif