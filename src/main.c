/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:34:25 by randrade          #+#    #+#             */
/*   Updated: 2025/06/23 14:10:14 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"


void print_elements(t_control_panel *control_panel)
{
    if (!control_panel)
    {
        fprintf(stderr, "Error: control_panel is NULL\n");
        return;
    }

    printf("Ambient Light:\n");
    printf("\t light_force = %.2f\n", control_panel->amb_light.light_force);
    printf("\t rgb = r-> %f g-> %f b-> %f\n", control_panel->amb_light.rgb[0], control_panel->amb_light.rgb[1], control_panel->amb_light.rgb[2]);

    printf("\nCamera:\n");
    printf("\t coord = x-> %.2f y-> %.2f z-> %.2f\n", control_panel->camera.cords[0], control_panel->camera.cords[1], control_panel->camera.cords[2]);
    printf("\t vector = x-> %.2f y-> %.2f z-> %.2f\n", control_panel->camera.vec3[0], control_panel->camera.vec3[1], control_panel->camera.vec3[2]);
    printf("\t fov = %d\n", control_panel->camera.fov);

    printf("\nLight:\n");
    printf("\t coord = x-> %.2f y-> %.2f z-> %.2f\n", control_panel->light.cords[0], control_panel->light.cords[1], control_panel->light.cords[2]);
    printf("\t brightness = %.2f\n", control_panel->light.brightness);
    printf("\t rgb = r-> %f g-> %f b-> %f\n", control_panel->light.rgb[0], control_panel->light.rgb[1], control_panel->light.rgb[2]);

    // Verificar se há esferas e se data.sphere_count é válido
    if (control_panel->sphere && control_panel->data.sphere_count > 0)
    {
        printf("\nSPHERES AFTER ARRAY CONVERSION:\n");
        for (size_t i = 0; i < control_panel->data.sphere_count; i++)
        {
            printf("\nSphere %zu:\n", i + 1);
            printf("\t coord = x-> %.2f y-> %.2f z-> %.2f\n",
                   control_panel->sphere[i].cords[0],
                   control_panel->sphere[i].cords[1],
                   control_panel->sphere[i].cords[2]);
            printf("\t d = %.2f (diameter)\n", control_panel->sphere[i].d);
            printf("\t radius = %.2f\n", control_panel->sphere[i].radius);
            printf("\t rgb = r-> %f g-> %f b-> %f\n",
                   control_panel->sphere[i].rgb[0],
                   control_panel->sphere[i].rgb[1],
                   control_panel->sphere[i].rgb[2]);
        }
    }
    else
    {
        printf("\nNo spheres found or sphere array is NULL\n");
    }

    // Verificar se há planos
	if (control_panel->plane && control_panel->data.plane_count > 0)
	{
		printf("\nPLANES AFTER ARRAY CONVERSION:\n");
		for (size_t i = 0; i < control_panel->data.plane_count; i++)
		{
			printf("\nPlane %zu:\n", i + 1);
			printf("\t coord = x-> %.2f y-> %.2f z-> %.2f\n",
				control_panel->plane[i].cords[0],
				control_panel->plane[i].cords[1],
				control_panel->plane[i].cords[2]);
			printf("\t vector = x-> %.2f y-> %.2f z-> %.2f\n",
				control_panel->plane[i].vec3[0],
				control_panel->plane[i].vec3[1],
				control_panel->plane[i].vec3[2]);
			printf("\t rgb = r-> %f g-> %f b-> %f\n",
				control_panel->plane[i].rgb[0],
				control_panel->plane[i].rgb[1],
				control_panel->plane[i].rgb[2]);
		}
	}
    else
    {
        printf("\nNo planes found or plane list is NULL\n");
    }
/*
    // Verificar se há cilindros
    if (control_panel->cylinder && control_panel->data.cylinder_count > 0)
    {
        t_cylinder *temp = control_panel->cylinder;
        int count = 0;
        while (temp && count < (int)control_panel->data.cylinder_count)
        {
            printf("\nCylinder %d:\n", count + 1);
            printf("\t coord = x-> %.2f y-> %.2f z-> %.2f\n", temp->cords[0], temp->cords[1], temp->cords[2]);
            printf("\t vector = x-> %.2f y-> %.2f z-> %.2f\n", temp->vec3[0], temp->vec3[1], temp->vec3[2]);
            printf("\t d = %.2f\n", temp->d);
            printf("\t radius = %.2f\n", temp->radius);
            printf("\t height = %.2f\n", temp->height);
            printf("\t rgb = r-> %f g-> %f b-> %f\n", temp->rgb[0], temp->rgb[1], temp->rgb[2]);
            temp = temp->next;
            count++;
        }
    }
    else
    {
        printf("\nNo cylinders found or cylinder list is NULL\n");
    }
		*/
}


void render_scene(t_control_panel *control_panel)
{
	int y;
	int x;
	int sample;
	t_ray ray;
	double pixel_color[3];
	int rgb;
	double sample_color[3];
	double pixel_samples_scale;
	t_mlx *mlx_data = control_panel->mlx;

	y = 0;
	while (y < control_panel->camera.image_height)
	{
		x = 0;
		while (x < control_panel->camera.image_width)
		{
			vec3_zero(pixel_color);
			if (!control_panel->camera.antialiasing)
			{
				ray = get_ray(x, y, control_panel);
				ray_color(control_panel,control_panel->camera.max_bounces, &ray, pixel_color);
			}
			else
			{
				sample = 0;
				while (control_panel->camera.samples_per_pixel > sample)
				{
					vec3_zero(sample_color);
					ray = get_ray(x, y, control_panel);
					ray_color(control_panel, control_panel->camera.max_bounces,&ray, sample_color);
					pixel_color[0] += sample_color[0];
					pixel_color[1] += sample_color[1];
					pixel_color[2] += sample_color[2];
					sample++;
				}

				// Calcular a média das amostras
				pixel_samples_scale = 1.0 / control_panel->camera.samples_per_pixel;
				pixel_color[0] *= pixel_samples_scale;
				pixel_color[1] *= pixel_samples_scale;
				pixel_color[2] *= pixel_samples_scale;
			}

			rgb = write_color(pixel_color[0], pixel_color[1], pixel_color[2]);
			my_mlx_pixel_put(control_panel, x, y, rgb);
			x++;
		}

		if (y % 10 == 0)
			ft_printf(BHYEL "\rScanlines remaining: %d " reset, (control_panel->camera.image_height - y));

		y++;
	}
	ft_printf(BHGRN "\rScanlines remaining: DONE!" reset "\n");
	mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, mlx_data->img, 0, 0);
	if (control_panel->camera.antialiasing)
		printf("\n" GRNHB BBLK "Antialiasing: ON" reset "\n");
	else
		printf("\n" REDHB BBLK "Antialiasing: OFF" reset "\n");
}

t_control_panel *inicialize(int argc, char *argv[])
{
	t_control_panel *control_panel;

	if (argc != 2)
		return (NULL);

	control_panel = ft_calloc(1, sizeof(t_control_panel));
	if (!control_panel)
		return (NULL);
	if (!parsing(control_panel, argv[1]))
	{
		print_parsing_error(control_panel->error_log);
		return (free_control_panel_lists(control_panel), NULL);
	}
	get_values_camera(control_panel);
	return control_panel;
}

int main(int argc, char *argv[])
{
	t_mlx mlx_data;
	t_control_panel *cp;

	cp = inicialize(argc, argv);
	if (!cp)
		return 1;

	print_elements(cp);
	ft_printf("MiniRT Starting...\n");
	srand(time(NULL));
	
	if(init_values_main_win(&mlx_data,cp))
		return 1;

	if(create_control_window(cp))
		return 1;
	// Renderizar a cena inicial
	render_scene(cp);

	// Configurar hooks
	mlx_hook(mlx_data.win, 17, 0, close_window, cp);
	mlx_key_hook(mlx_data.win, key_hook, cp);

	mlx_loop(mlx_data.mlx);
	return (0);
}
