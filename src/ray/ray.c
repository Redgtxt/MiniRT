/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 18:39:18 by ruigoncalve       #+#    #+#             */
/*   Updated: 2025/09/30 18:45:33 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_ray get_ray(int i, int j, t_control_panel *control_panel)
{
    double offset[3];
    double pixel_sample[3];
    double pixel_offset_u[3];
    double pixel_offset_v[3];
    double ray_direction[3];
    t_ray ray;

    vec3_zero(offset);

    // Obter um offset aleatório para anti-aliasing
    if (control_panel->camera.antialiasing)
        sample_square(offset);

    // Calcular o ponto de amostragem do pixel com offset
    // pixel_sample = pixel00_loc + (i + offset.x) * pixel_delta_u + (j + offset.y) * pixel_delta_v
    vec3_scale(pixel_offset_u, control_panel->camera.pixel_delta_u, i + offset[0]);
    vec3_scale(pixel_offset_v, control_panel->camera.pixel_delta_v, j + offset[1]);

    // Primeiro adiciona pixel00_loc + pixel_offset_u
    vec3_add(pixel_sample, control_panel->camera.pixel00_loc, pixel_offset_u);
    // Depois adiciona o resultado anterior + pixel_offset_v
    vec3_add(pixel_sample, pixel_sample, pixel_offset_v);

    // ray_direction = pixel_sample - ray_origin (camera center)
    vec3_sub(ray_direction, pixel_sample, control_panel->camera.cords);

    // Criar e retornar o ray com origem na câmera e direção para o pixel
    create_ray(&ray, control_panel->camera.cords, ray_direction);

    return ray;
}

void	set_amb_light(t_control_panel *control_panel, const t_ray *ray, double out_color[3])
{
    double unit_direction[3];
    double white[3] = {1.0, 1.0, 1.0};
    double temp[3];

    // // Background - gradient from white to blue
    vec3_normalize(unit_direction, ray->direction);
    double a = 0.5 * (unit_direction[1] + 1.0);

    // // Calculate (1.0-a)*white + a*blue
    vec3_scale(out_color, white, control_panel->amb_light.light_force - a);
    vec3_scale(temp, control_panel->amb_light.rgb, a);
    vec3_add(out_color, out_color, temp);

    // Apply ambient light color scaled by its force
    vec3_scale(out_color, out_color, control_panel->amb_light.light_force);
}

void ray_color(t_control_panel *panel, int depth, const t_ray *ray, double out_color[3])
{
    t_hit_record rec;

    if (depth <= 0)
    {
        vec3_zero(out_color);
        return;
    }

    if (hit_world(panel, ray, interval_create(0.001, D_INFINITY), &rec))
    {
        t_data_scatter data_scatter;
        vec3 color[3] = {0, 0, 0};
        size_t	i;

        // For glass materials, skip direct lighting and go straight to scattering
        if (rec.material->type != GLASS)
        {
            i = 0;
            while (i < panel->data.light_count)
            {
            	// Process each light source
            	vec3 light_dir[3];
            	vec3_sub(light_dir, panel->light[i].cords, rec.position);
            	double distance = vec3_length(light_dir);
            	
            	// Get shadow intensity (1.0 = no shadow, 0.0 = full shadow)
            	double shadow_intensity = get_shadow_intensity(panel, rec.position, &panel->light[i]);
            	
            	if (shadow_intensity > 0.0)
            	{
                	vec3_normalize(light_dir, light_dir);

                	// Apply realistic light attenuation
                	double attenuation = 1.0 / (LIGHT_CONSTANT + LIGHT_LINEAR * distance + LIGHT_QUADRATIC * distance * distance);
                	
                	// Apply shadow intensity to attenuation
                	attenuation *= shadow_intensity;
                	
                	// Alternative: Simple inverse square with minimum distance
                	// double attenuation = 1.0 / fmax(distance * distance, 1.0);

                	// Diffuse component
                	diffuse_comp(&panel->light[i], &rec, color, light_dir, attenuation);

                	// Specular component (Phong)
                	if (rec.material->shininess > 0) {
                    	vec3 view_dir[3];
                    	vec3_negate(view_dir, ray->direction);
                    	vec3_normalize(view_dir, view_dir);

                    	vec3 reflect_dir[3];
                    	reflect(light_dir, rec.normal, reflect_dir);

                    	double spec = pow(fmax(vec3_dot(view_dir, reflect_dir), 0.0),
                           	rec.material->shininess);
                    	vec3 specular[3];
                    	vec3_scale(specular, rec.material->specular, spec * SPECULAR_INTENSITY);
                    	vec3_multiply(specular, specular, panel->light[i].rgb);
                    	vec3_scale(specular, specular, panel->light[i].brightness * attenuation);
                    	vec3_add(color, color, specular);
                	}
            	}
             	i++;
            }
        }

        	// Recursive reflection/refraction for all materials
        	if (scatter(rec.material, ray, &rec, &data_scatter)) {
            	vec3 scattered_color[3];
            	ray_color(panel, depth - 1, &data_scatter.scattered, scattered_color);
            	vec3_multiply(scattered_color, scattered_color, data_scatter.attenuation);
            	vec3_add(color, color, scattered_color);
        	}
        	vec3_copy(out_color, color);
    }
    else
        set_amb_light(panel, ray, out_color);
}