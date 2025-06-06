/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:34:25 by randrade          #+#    #+#             */
/*   Updated: 2025/06/06 16:04:48 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	print_elements(t_control_panel *control_panel)
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
            printf("\nSphere %zu:\n", i+1);
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


/*Vai returnar o ponto onde bateu*/
/*

    Vamos fazer umas contas para descobrir se colidimos com a esfera, se returnar uma raiz significa que batemos na "levemente"
    se returnar mais que 1 BATEMOS NA totalidade na esfera
    0 siginifca que nao batemos
*/
/* double	hit_sphere(const double center[3], double radius, const t_ray *r)
{
	double	oc[3];
	double	discriminant;

	vec3_sub(oc, center, r->origin);               // oc = center - r->origin
	double a = vec3_lenght(r->direction);          // direction.length_squared()
	double h = vec3_dot(r->direction, oc);         // dot(direction, oc)
	double c = vec3_lenght(oc) - radius * radius;  // oc.length_squared()- radius²
	discriminant = h * h - a * c;
	if (0 > discriminant)
	{
		return (-1.0);
	}
	else
	{
		return ((h - sqrt(discriminant)) / a);
	}
} */

/* void	ray_color(t_control_panel *control_panel, const t_ray *ray, double out_color[3])
{
	double	t;
	double hit_point[3];
	double normal[3];
	double unit_normal[3];
	double	unit_direction[3];
	double	a;
	double	white[3] = {1.0, 1.0, 1.0};
	double	blue[3] = {0.5, 0.7, 1.0};
	double	scaled_white[3], scaled_blue[3];

	t = hit_sphere(control_panel->sphere->cords, control_panel->sphere->radius, ray);
	if (t > 0.0)
	{
		// Calcule o ponto de colisão
		ray_at(t, *ray, hit_point);
		// Calcule o vetor normal (N = point_of_collision - sphere_center)
		vec3_sub(normal, hit_point, control_panel->sphere->cords);
		// Normalize o vetor
		vec3_unit_vector(unit_normal, normal);
		// Mapeie a normal para cor: 0.5 * color(N.x+1, N.y+1, N.z+1)
		// Isso mapeia a normal de [-1,1] para cor [0,1]
		out_color[0] = 0.5 * (unit_normal[0] + 1.0);
		out_color[1] = 0.5 * (unit_normal[1] + 1.0);
		out_color[2] = 0.5 * (unit_normal[2] + 1.0);
		return ;
	}
	// Nao atingi a esfera vou desenhar o fundo
	normalize_vec(unit_direction, ray->direction);
	a = 0.5 * (unit_direction[1] + 1.0);
	// INICIALIZAR out_color com zeros
	vec3_zero(out_color);
	vec3_scale(scaled_white, white, 1.0 - a);
	vec3_scale(scaled_blue, blue, a);
	vec3_add(out_color, scaled_white, scaled_blue);
} */
 
int	write_color(double r, double g, double b)
{
	int	ir;
	int	ig;
	int	ib;

	ir = (int)(255.999 * r);
	ig = (int)(255.999 * g);
	ib = (int)(255.999 * b);
	return ((ir << 16) | (ig << 8) | ib);
}
 
int	main(int argc, char *argv[])
{
	    t_mlx       mlx_data;
	double		aspect_ratio;
	double		focal_lenght;
	double		viewport_height;
	double		viewport_width;
	double		viewport_horizontal[3];
	double		viewport_vertical[3];
	double		pixel_delta_horizontal[3];
	double		pixel_delta_vertical[3];
	double		viewport_upper_left[3];
	double		focal_offset[3];
	double		viewport_h_half[3];
	double		viewport_v_half[3];
	double		pixel00_loc[3];
	double		pixel_delta_sum[3];
	double		half_delta[3];
	int			y;
	int			x;
	double pixel_center[3];
	double pixel_h[3];
	double pixel_v[3];
	double sum_pixel[3];
	double ray_direction[3];
	t_ray ray;
	double pixel_color[3];
	int			rgb;
    t_control_panel *control_panel;

    if (argc != 2)
        return (1);
    control_panel = ft_calloc(1, sizeof(t_control_panel));
    if (!control_panel)
        return (1);
    if (!parsing(control_panel, argv[1]))
    {
   		print_parsing_error(control_panel->error_log);
     	return (free_control_panel(control_panel), 1);
    }
	/*
		Init viewport
	*/
	// Image
	aspect_ratio = 16.0 / 9.0;
   	mlx_data.width = WINDOW_WIDTH;
	 mlx_data.width  = mlx_data.width;
	// Vamos ver se a image_height fica em pelo menos 1
	// Arredondo o valor
    mlx_data.height = (int)mlx_data.width / aspect_ratio;
	  mlx_data.height = mlx_data.height;
    if (mlx_data.height < 1)
	{
        mlx_data.height = 1;
	}
    
	// viewport width
	focal_lenght = 1.0;
	viewport_height = 2.0;
	viewport_width = viewport_height * ((double)mlx_data.width / (double)mlx_data.height);
	/*
		Aqui criamos o quadrado do viewport
	*/
	vec3_set(viewport_horizontal, viewport_width, 0, 0);
	vec3_set(viewport_vertical, 0, -viewport_height, 0);
	/*
		Aqui criamos os pixeis dentro viewport
	*/
	vec3_divide(pixel_delta_horizontal, viewport_horizontal,
		(double)mlx_data.width );
	vec3_divide(pixel_delta_vertical, viewport_vertical, (double) mlx_data.height);
	/*
		Agora vamos capturar o primeiro pixel
	*/
	vec3_set(focal_offset, 0, 0, focal_lenght);
	vec3_divide(viewport_h_half, viewport_horizontal, 2.0);
	vec3_divide(viewport_v_half, viewport_vertical, 2.0);
	// viewport_upper_left = camera_center - focal_offset- viewport_horizontal/2 - viewport_vertical/2
	vec3_sub_chain(viewport_upper_left, control_panel->camera.cords, focal_offset,
		viewport_h_half, viewport_v_half);
	vec3_add(pixel_delta_sum, pixel_delta_horizontal, pixel_delta_vertical);
	vec3_scale(half_delta, pixel_delta_sum, 0.5);
	// Consegui a localizacao do primeiro pixel
	vec3_add(pixel00_loc, viewport_upper_left, half_delta);
	print_elements(control_panel);
	ft_printf("MiniRT Starting...\n");
    mlx_data.mlx = mlx_init();
    if (!mlx_data.mlx)
    {
        ft_printf("Error: Could not initialize MLX\n");
        return (1);
    }
    
   mlx_data.win = mlx_new_window(mlx_data.mlx, mlx_data.width, mlx_data.height, "miniRT");
    if (!mlx_data.win)
    {
        ft_printf("Error: Could not create window\n");
        return (1);
    }

	 mlx_data.img = mlx_new_image(mlx_data.mlx, mlx_data.width, mlx_data.height);
    mlx_data.addr = mlx_get_data_addr(mlx_data.img, &mlx_data.bits_per_pixel, 
                                     &mlx_data.line_length, &mlx_data.endian);
	y = 0;
    while (y < mlx_data.height)
	{
		x = 0;
        while (x < mlx_data.width)
		{
			// pixel_center = pixel00_loc + (x * pixel_delta_horizontal) + (y* pixel_delta_vertical)
			vec3_scale(pixel_h, pixel_delta_horizontal, x);
			vec3_scale(pixel_v, pixel_delta_vertical, y);
			vec3_add(sum_pixel, pixel_h, pixel_v);
			// Estou a andar para a  posicao de onde o raio vai sair
			vec3_add(pixel_center, pixel00_loc, sum_pixel);
			vec3_sub(ray_direction, pixel_center, control_panel->camera.cords);
			create_ray(&ray, control_panel->camera.cords, ray_direction);
			ray_color(control_panel, &ray, pixel_color);
			rgb = write_color(pixel_color[0], pixel_color[1], pixel_color[2]);
          	my_mlx_pixel_put(&mlx_data, x, y, rgb);
			x++;
		}
		y++;
	}

	mlx_put_image_to_window(mlx_data.mlx, mlx_data.win, mlx_data.img, 0, 0);
	ft_printf("Render Completed\n");
	game_hooks(&mlx_data);
	mlx_loop(mlx_data.mlx);
	return (0);
} 


// int	main(int argc, char *argv[])
// {
// 	    t_mlx       mlx_data;
// 	double		aspect_ratio;
// 	double		focal_lenght;
// 	double		viewport_height;
// 	double		viewport_width;
// 	double		viewport_horizontal[3];
// 	double		viewport_vertical[3];
// 	double		pixel_delta_horizontal[3];
// 	double		pixel_delta_vertical[3];
// 	double		viewport_upper_left[3];
// 	double		focal_offset[3];
// 	double		viewport_h_half[3];
// 	double		viewport_v_half[3];
// 	double		pixel00_loc[3];
// 	double		pixel_delta_sum[3];
// 	double		half_delta[3];
// 	int			y;
// 	int			x;
// 			double pixel_center[3];
// 			double pixel_h[3];
// 			double pixel_v[3];
// 			double sum_pixel[3];
// 			double ray_direction[3];
// 			t_ray ray;
// 			double pixel_color[3];
// 	int			rgb;
//     t_control_panel *control_panel;

//     if (argc != 2)
//         return (1);
//     control_panel = ft_calloc(1, sizeof(t_control_panel));
//     if (!control_panel)
//         return (1);
//     if (!parsing(control_panel, argv[1]))
//     {
//    		print_parsing_error(control_panel->error_log);
//      	return (free_control_panel(control_panel), 1);
//     }
// 	/*
// 		Init viewport
// 	*/
// 	// Image
// 	aspect_ratio = 16.0 / 9.0;
//    	mlx_data.width = WINDOW_WIDTH;
// 	 mlx_data.width  = mlx_data.width;
// 	// Vamos ver se a image_height fica em pelo menos 1
// 	// Arredondo o valor
//     mlx_data.height = (int)mlx_data.width / aspect_ratio;
// 	  mlx_data.height = mlx_data.height;
//     if (mlx_data.height < 1)
// 	{
//         mlx_data.height = 1;
// 	}
    
// 	// viewport width
// 	focal_lenght = 1.0;
// 	viewport_height = 2.0;
// 	viewport_width = viewport_height * ((double)mlx_data.width / (double)mlx_data.height);
// 	/*
// 		Aqui criamos o quadrado do viewport
// 	*/
// 	vec3_set(viewport_horizontal, viewport_width, 0, 0);
// 	vec3_set(viewport_vertical, 0, -viewport_height, 0);
// 	/*
// 		Aqui criamos os pixeis dentro viewport
// 	*/
// 	vec3_divide(pixel_delta_horizontal, viewport_horizontal,
// 		(double)mlx_data.width );
// 	vec3_divide(pixel_delta_vertical, viewport_vertical, (double) mlx_data.height);
// 	/*
// 		Agora vamos capturar o primeiro pixel
// 	*/
// 	vec3_set(focal_offset, 0, 0, focal_lenght);
// 	vec3_divide(viewport_h_half, viewport_horizontal, 2.0);
// 	vec3_divide(viewport_v_half, viewport_vertical, 2.0);
// 	// viewport_upper_left = camera_center - focal_offset- viewport_horizontal/2 - viewport_vertical/2
// 	vec3_sub_chain(viewport_upper_left, control_panel->camera.cords, focal_offset,
// 		viewport_h_half, viewport_v_half);
// 	vec3_add(pixel_delta_sum, pixel_delta_horizontal, pixel_delta_vertical);
// 	vec3_scale(half_delta, pixel_delta_sum, 0.5);
// 	// Consegui a localizacao do primeiro pixel
// 	vec3_add(pixel00_loc, viewport_upper_left, half_delta);
// 	print_elements(control_panel);
// 	ft_printf("MiniRT Starting...\n");
//     mlx_data.mlx = mlx_init();
//     if (!mlx_data.mlx)
//     {
//         ft_printf("Error: Could not initialize MLX\n");
//         return (1);
//     }
    
//    mlx_data.win = mlx_new_window(mlx_data.mlx, mlx_data.width, mlx_data.height, "miniRT");
//     if (!mlx_data.win)
//     {
//         ft_printf("Error: Could not create window\n");
//         return (1);
//     }

// 	 mlx_data.img = mlx_new_image(mlx_data.mlx, mlx_data.width, mlx_data.height);
//     mlx_data.addr = mlx_get_data_addr(mlx_data.img, &mlx_data.bits_per_pixel, 
//                                      &mlx_data.line_length, &mlx_data.endian);
// 	y = 0;
//     while (y < mlx_data.height)
// 	{
// 		x = 0;
//         while (x < mlx_data.width)
// 		{
// 			// pixel_center = pixel00_loc + (x * pixel_delta_horizontal) + (y* pixel_delta_vertical)
// 			vec3_scale(pixel_h, pixel_delta_horizontal, x);
// 			vec3_scale(pixel_v, pixel_delta_vertical, y);
// 			vec3_add(sum_pixel, pixel_h, pixel_v);
// 			// Estou a andar para a  posicao de onde o raio vai sair
// 			vec3_add(pixel_center, pixel00_loc, sum_pixel);
// 			vec3_sub(ray_direction, pixel_center, control_panel->camera.cords);
// 			create_ray(&ray, control_panel->camera.cords, ray_direction);
// 			ray_color(control_panel, &ray, pixel_color);
// 			rgb = write_color(pixel_color[0], pixel_color[1], pixel_color[2]);
//           	my_mlx_pixel_put(&mlx_data, x, y, rgb);
// 			x++;
// 		}
// 		y++;
// 	}

// 	mlx_put_image_to_window(mlx_data.mlx, mlx_data.win, mlx_data.img, 0, 0);
// 	ft_printf("Render Completed\n");
// 	game_hooks(&mlx_data);
// 	mlx_loop(mlx_data.mlx);
// 	return (0);
// } 

/* 
int main(int argc, char *argv[])
{
    t_control_panel *control_panel;

    if (argc != 2)
        return (1);
    control_panel = ft_calloc(1, sizeof(t_control_panel));
    if (!control_panel)
        return (1);
    if (!parsing(control_panel, argv[1]))
    {
   		print_parsing_error(control_panel->error_log);
     	return (free_control_panel(control_panel), 1);
    }
   	print_elements(control_panel);
    free_control_panel(control_panel);
    return (0);
}
 */

    // void *mlx;
    // void *mlx_win;

    // ft_printf("MiniRT Starting...\n");

    // mlx = mlx_init();
    // if (!mlx)
    // {
    //     ft_printf("Error: Could not initialize MLX\n");
    //     return (1);
    // }

    // mlx_win = mlx_new_window(mlx, WINDOW_HEIGHT, WINDOW_WIDTH, "miniRT");
    // if (!mlx_win)
    // {
    //     ft_printf("Error: Could not create window\n");
    //     return (1);
    // }

    // int i = 0;
    // while (WINDOW_HEIGHT >= i)
    // {

    //     int j = 0;

    //     while (WINDOW_WIDTH >= j)
    //     {
    //         mlx_pixel_put(mlx, mlx_win, i,j, 0x0000FF);
    //         mlx_pixel_put(mlx, mlx_win, i,0, 0xFF0000);
    //        j++;
    //     }

    //     i++;
    // }


    // ft_printf("Window created successfully\n");
    // mlx_loop(mlx);
