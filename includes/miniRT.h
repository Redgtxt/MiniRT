/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <randrade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:40:49 by randrade          #+#    #+#             */
/*   Updated: 2025/10/08 15:42:08 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

/* Standard C libraries */
# include <errno.h>
# include <fcntl.h>
# include <float.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <time.h>
# include <unistd.h>

/* External libraries */
# include "../Library/ft_printf/ft_printf.h"
# include "../Library/get_next_line/get_next_line.h"
# include "../Library/libft/libft.h"
# include "../Library/minilibx-linux/mlx.h"

/* Core includes */
# include "core/constants.h"
# include "core/types.h"

/* Math includes */
# include "math/interval.h"
# include "math/vec3.h"

/* Graphics includes */
# include "graphics/camera.h"
# include "graphics/lighting.h"
# include "graphics/materials.h"
# include "graphics/ray.h"
# include "graphics/render.h"

/* Object includes */
# include "objects/cone.h"
# include "objects/cylinder.h"
# include "objects/objects.h"
# include "objects/plane.h"
# include "objects/sphere.h"

/* System includes */
# include "system/memory.h"
# include "system/mlx_wrapper.h"

/* UI includes */
# include "ui/ui.h"

/* I/O includes */
# include "io/errors.h"
# include "io/parsing.h"

/* Main control panel */
# include "core/control_panel.h"

#endif
