/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <randrade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:40:49 by randrade          #+#    #+#             */
/*   Updated: 2025/05/27 16:11:15 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include "../Library/ft_printf/ft_printf.h"
# include "../Library/get_next_line/get_next_line.h"
# include "../Library/libft/libft.h"
# include "../Library/minilibx-linux/mlx.h"
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>

# define WINDOW_HEIGHT 800
# define WINDOW_WIDTH 600

typedef unsigned char	mini_int;


typedef struct s_rgb
{
	mini_int			R;
	mini_int			G;
	mini_int			B;
}						t_rgb;

typedef struct s_amb_light
{
	float				light_force;
	t_rgb				rgb;
}						t_amb_light;

typedef struct s_camera
{
	double				coord[3];
	float				vector[3];
	mini_int			fov;
}						t_camera;

typedef struct s_light
{
	double				coord[3];
	float				brightness;
	t_rgb rgb; // nao e usado no mandatory
}						t_light;

typedef struct s_sphere
{
	// coordenadas do centro da esfera
	double				coord[3];
	/*Diametro da Espera
	(E passado no subject)
	*/
	double				d;
	// Acho que e fixe ter para calculos (vamos ter de o calcular)
	double				radius;
	t_rgb				rgb;
	struct s_sphere		*prev;
	struct s_sphere		*next;
}						t_sphere;

typedef struct s_plane
{
	//    PODE NAO SER O CENTRO (PELOS VISTOS PLANOS SAO INFINITOS)
	double				coord[3];
	float				vector[3];
	t_rgb				rgb;
	struct s_plane		*prev;
	struct s_plane		*next;
}						t_plane;

typedef struct s_cylinder
{
	//     coordenadas do centro do CILINDRO
	t_coord				coord;
	t_vector			vector;
	/*
	Diametro do CILINDRO(E passado no subject)
	*/
	double				d;
	// Acho que e fixe ter para calculos (vamos ter de o calcular)
	double				radius;
	double				height;
	t_rgb				rgb;
	struct s_cylinder	*prev;
	struct s_cylinder	*next;

}						t_cylinder;

typedef struct s_control_panel
{
	t_amb_light			amb_light;
	t_camera			camera;
	t_light				light;
	t_sphere			*sphere;
	t_plane				*plane;
	t_cylinder			*cylinder;
}						t_control_panel;


//	Parsing.c
bool	parsing(t_control_panel *control_panel, char *file_name);

//	Utils.c
char	**split_spaces(char const *s);

#endif
