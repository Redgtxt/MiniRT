/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materials.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 00:00:00 by ruigoncalve      #+#    #+#             */
/*   Updated: 2025/10/03 00:00:00 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIALS_H
# define MATERIALS_H

# include "../core/types.h"

/* Material structure */
typedef struct s_mt
{
	t_material_type	type;
	double			albedo[3];
	double			specular[3];
	double			shininess;
	double			checker_scale;
	double			refraction_index;
}					t_material;

/* Material scatter data */
typedef struct s_data_scatter
{
	t_ray			scattered;
	double			attenuation[3];
}					t_data_scatter;

/* Material function prototypes */
bool				scatter(const t_material *mat, const t_ray *r_in,
						t_hit_record *rec, t_data_scatter *data_scatter);
bool				lambertian_scatter(t_hit_record *rec,
						t_data_scatter *data_scatter);
bool				metal_scatter(const t_ray *r_in, t_hit_record *rec,
						t_data_scatter *data_scatter);
bool				glass_scatter(const t_ray *r_in, t_hit_record *rec,
						t_data_scatter *data_scatter);
bool				checker_scatter(t_hit_record *rec,
						t_data_scatter *data_scatter);
bool				solid_scatter(t_control_panel *panel, t_hit_record *rec,
						vec3 color[3]);

/* Material setup functions */
void				set_lambertian_material(t_material *material,
						double rgb[3]);
void				set_metal_material(t_material *material, double rgb[3]);
void				set_glass_material(t_material *material);
void				set_checker_material(t_material *material, double rgb[3]);
void				set_solid_material(t_material *material, double rgb[3]);

#endif