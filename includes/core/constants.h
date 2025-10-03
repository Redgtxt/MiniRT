/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 00:00:00 by ruigoncalve      #+#    #+#             */
/*   Updated: 2025/10/03 00:00:00 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# include <float.h>
# include <limits.h>

/* Printf colors */
# define REDHB "\e[0;101m"
# define GRNHB "\e[0;102m"
# define BBLK "\e[1;30m"
# define BRED "\e[1;31m"
# define BHGRN "\e[1;92m"
# define BHYEL "\e[1;93m"
# define HMAG "\e[1;95m"
# define RESET "\e[0m"

/* Camera and rendering constants */
# define MAX_CAMERA_BOUNCES 10

/* Light intensity control constants */
# define DIFFUSE_INTENSITY 1.5
# define SPECULAR_INTENSITY 1.2

/* Light attenuation constants (realistic lighting) */
# define LIGHT_CONSTANT 1.0
# define LIGHT_LINEAR 0.045
# define LIGHT_QUADRATIC 0.016

/* Mathematical constants */
# define PI 3.1415926535897932385
# define D_INFINITY ((double)INFINITY)

/* Overflow limits */
# define OVERFLOW_MAX_LIMIT 2147483647
# define OVERFLOW_MIN_LIMIT -2147483648

#endif