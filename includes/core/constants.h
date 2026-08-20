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

# include <limits.h>
# include <math.h>

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

/* Light intensity control constants (physically-based = 1.0) */
# define DIFFUSE_INTENSITY 1.0
# define SPECULAR_INTENSITY 2.0

/* Light attenuation constants (realistic lighting) */
# define LIGHT_CONSTANT 1.0
# define LIGHT_LINEAR 0.045
# define LIGHT_QUADRATIC 0.016

/* Mathematical constants */
# define PI 3.1415926535897932385
# define D_INFINITY INFINITY

/* Overflow limits */
# define OVERFLOW_MAX_LIMIT 2147483647
# define OVERFLOW_MIN_LIMIT -2147483648

/* Lambertian material properties (matte/diffuse surfaces) */
# define LAMBERTIAN_SPECULAR 0.1
# define LAMBERTIAN_SHININESS 10.0
# define LAMBERTIAN_REFRACTION_INDEX 1.0

/* Metal material properties (polished, reflective surfaces) */
# define METAL_SPECULAR 1.0
# define METAL_SHININESS 96.0
# define METAL_REFRACTION_INDEX 1.0
/* Balance between reflection and direct lighting for metals */
# define METAL_DIFFUSE_SCALE 0.4
# define METAL_REFLECTION_SCALE 0.6

/* Glass material properties (transparent, refractive - standard glass IOR) */
# define GLASS_SPECULAR 0.7
# define GLASS_SHININESS 120.0
# define GLASS_REFRACTION_INDEX 1.5

/* Checker pattern material properties (matte surface) */
# define CHECKER_SPECULAR 0.5
# define CHECKER_SHININESS 64.0
# define CHECKER_SCALE 0.5

/* Solid material properties (semi-gloss surfaces like plastic, painted wood) */
# define SOLID_SPECULAR 0.5
# define SOLID_SHININESS 64.0
# define SOLID_REFRACTION_INDEX 1.0

#endif