/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:34:25 by randrade          #+#    #+#             */
/*   Updated: 2025/06/11 19:09:30 by hguerrei         ###   ########.fr       */
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
	printf("\t rgb = r-> %f g-> %f b-> %f\n", control_panel->amb_light.rgb.r, control_panel->amb_light.rgb.g, control_panel->amb_light.rgb.b);

	printf("\nCamera:\n");
	printf("\t coord = x-> %.2f y-> %.2f z-> %.2f\n", control_panel->camera.cords[0], control_panel->camera.cords[1], control_panel->camera.cords[2]);
	printf("\t vector = x-> %.2f y-> %.2f z-> %.2f\n", control_panel->camera.vec3[0], control_panel->camera.vec3[1], control_panel->camera.vec3[2]);
	printf("\t fov = %d\n", control_panel->camera.fov);

	printf("\nLight:\n");
	printf("\t coord = x-> %.2f y-> %.2f z-> %.2f\n", control_panel->light.cords[0], control_panel->light.cords[1], control_panel->light.cords[2]);
	printf("\t brightness = %.2f\n", control_panel->light.brightness);
	printf("\t rgb = r-> %f g-> %f b-> %f\n", control_panel->light.rgb.r, control_panel->light.rgb.g, control_panel->light.rgb.b);

	if (control_panel->sphere)
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
				   control_panel->sphere[i].rgb.r,
				   control_panel->sphere[i].rgb.g,
				   control_panel->sphere[i].rgb.b);
		}
	}
	else
	{
		fprintf(stderr, "Warning: sphere is NULL\n");
	}

	if (control_panel->plane)
	{
		t_plane *temp = control_panel->plane;
		while (temp)
		{
			printf("\nPlane:\n");
			printf("\t coord = x-> %.2f y-> %.2f z-> %.2f\n", temp->cords[0], temp->cords[1], temp->cords[2]);
			printf("\t vector = x-> %.2f y-> %.2f z-> %.2f\n", temp->vec3[0], temp->vec3[1], temp->vec3[2]);
			printf("\t rgb = r-> %f g-> %f b-> %f\n", temp->rgb.r, temp->rgb.g, temp->rgb.b);
			temp = temp->next;
		}
	}
	else
	{
		fprintf(stderr, "Warning: plane is NULL\n");
	}

	if (control_panel->cylinder)
	{
		t_cylinder *temp = control_panel->cylinder;
		while (temp)
		{
			printf("\nCylinder:\n");
			printf("\t coord = x-> %.2f y-> %.2f z-> %.2f\n", temp->cords[0], temp->cords[1], temp->cords[2]);
			printf("\t vector = x-> %.2f y-> %.2f z-> %.2f\n", temp->vec3[0], temp->vec3[1], temp->vec3[2]);
			printf("\t d = %.2f\n", temp->d);
			printf("\t radius = %.2f\n", temp->radius);
			printf("\t height = %.2f\n", temp->height);
			printf("\t rgb = r-> %f g-> %f b-> %f\n", temp->rgb.r, temp->rgb.g, temp->rgb.b);
			temp = temp->next;
		}
	}
	else
	{
		fprintf(stderr, "Warning: cylinder is NULL\n");
	}
}
int write_color(double r, double g, double b)
{
	int ir;
	int ig;
	int ib;
	t_interval intensity;

    // Translate the [0,1] component values to the byte range [0,255].
	intensity = interval_create(0.000, 0.999);
	ir = (int)(256 * clamp(r,intensity));
	ig = (int)(256 * clamp(g,intensity));
	ib = (int)(256 * clamp(b,intensity));
	return ((ir << 16) | (ig << 8) | ib);
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
            if(!control_panel->camera.antialiasing)
            {
                ray = get_ray(x, y, control_panel);
                ray_color(control_panel, &ray, pixel_color);
            }
            else
            {				
                sample = 0;
                while (control_panel->camera.samples_per_pixel > sample)
                {
                    vec3_zero(sample_color);
                    ray = get_ray(x, y, control_panel);
                    ray_color(control_panel, &ray, sample_color);
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
            my_mlx_pixel_put(control_panel, mlx_data, x, y, rgb);
            x++;
        }
        
        // Mostrar progresso do renderizador (opcional)
        if (y % 10 == 0)
            ft_printf(BHYEL "\rScanlines remaining: %d " reset, (control_panel->camera.image_height - y));
        
        y++;
    }
    ft_printf(BHGRN "\rScanlines remaining: DONE!" reset "\n");
    mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, mlx_data->img, 0, 0);
	if(control_panel->camera.antialiasing)
		printf("\n" GRNHB BBLK"Antialiasing: ON" reset "\n" );
	else
    	printf("\n" REDHB BBLK"Antialiasing: OFF" reset "\n" );
}

void setup_antialiasing(t_control_panel *control_panel)
{
	static bool first_time = true;

	  if(control_panel->camera.antialiasing)
        {
            control_panel->camera.samples_per_pixel = 100;
			printf("\n" HMAG "Antialiasing: APPLYING" reset "\n" );
        }
        else
        {
			if(!first_time)
				printf("\n" HMAG "Antialiasing: REMOVING" reset "\n" );
			else
				first_time = false;	
            control_panel->camera.samples_per_pixel = 1;
        }
        
        // Recalcular a escala de amostras
        control_panel->camera.pixel_samples_scale = 1.0 / control_panel->camera.samples_per_pixel;
}

static void setup_camera_dimensions(t_control_panel *control_panel)
{
	control_panel->camera.aspect_ratio = 16.0 / 9.0;
	setup_antialiasing(control_panel);
	control_panel->camera.image_width = WINDOW_WIDTH;
	control_panel->camera.image_height = (int)control_panel->camera.image_width / control_panel->camera.aspect_ratio;
	if (control_panel->camera.image_height < 1)
	{
		control_panel->camera.image_height = 1;
	}
}

static void setup_camera_viewport(t_control_panel *control_panel)
{
	double focal_lenght = 1.0;
	double viewport_height = 2.0;
	double viewport_width = viewport_height * ((double)control_panel->camera.image_width / (double)control_panel->camera.image_height);
	double viewport_horizontal[3], viewport_vertical[3];
	double focal_offset[3], viewport_h_half[3], viewport_v_half[3];
	double viewport_upper_left[3], pixel_delta_sum[3], half_delta[3], temp[3];

	vec3_set(viewport_horizontal, viewport_width, 0, 0);
	vec3_set(viewport_vertical, 0, -viewport_height, 0);
	vec3_divide(control_panel->camera.pixel_delta_u, viewport_horizontal, (double)control_panel->camera.image_width);
	vec3_divide(control_panel->camera.pixel_delta_v, viewport_vertical, (double)control_panel->camera.image_height);
	vec3_set(focal_offset, 0, 0, focal_lenght);
	vec3_divide(viewport_h_half, viewport_horizontal, 2.0);
	vec3_divide(viewport_v_half, viewport_vertical, 2.0);
	vec3_sub_chain(temp, control_panel->camera.cords, focal_offset, viewport_h_half);
	vec3_sub(viewport_upper_left, temp, viewport_v_half);
	vec3_add(pixel_delta_sum, control_panel->camera.pixel_delta_u, control_panel->camera.pixel_delta_v);
	vec3_scale(half_delta, pixel_delta_sum, 0.5);
	vec3_add(control_panel->camera.pixel00_loc, viewport_upper_left, half_delta);
}

void get_values_camera(t_control_panel *control_panel)
{
	setup_camera_dimensions(control_panel);
	setup_camera_viewport(control_panel);
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
		return (free_control_panel(control_panel), NULL);
	}
	get_values_camera(control_panel);
	return control_panel;
}

int main(int argc, char *argv[])
{
    t_mlx mlx_data;
    t_control_panel *control_panel;
    
    control_panel = inicialize(argc, argv);
    if (!control_panel)
        return 1;

    print_elements(control_panel);
    ft_printf("MiniRT Starting...\n");
    srand(time(NULL));
    mlx_data.mlx = mlx_init();
    if (!mlx_data.mlx)
    {
        ft_printf("Error: Could not initialize MLX\n");
        return (1);
    }

    mlx_data.win = mlx_new_window(mlx_data.mlx, control_panel->camera.image_width, control_panel->camera.image_height, "miniRT");
    if (!mlx_data.win)
    {
        ft_printf("Error: Could not create window\n");
        return (1);
    }

    mlx_data.img = mlx_new_image(mlx_data.mlx, control_panel->camera.image_width, control_panel->camera.image_height);
    mlx_data.addr = mlx_get_data_addr(mlx_data.img, &mlx_data.bits_per_pixel,
                                     &mlx_data.line_length, &mlx_data.endian);
    
    // Armazenar a estrutura mlx_data dentro de control_panel para acesso nas callbacks
    control_panel->mlx = &mlx_data;
    
    // Renderizar a cena inicial
    render_scene(control_panel);
    
    // Configurar hooks
	mlx_hook(mlx_data.win, 17, 0, close_window, &mlx_data);
    mlx_key_hook(mlx_data.win, key_hook, control_panel);
    
    mlx_loop(mlx_data.mlx);
    return (0);
}
