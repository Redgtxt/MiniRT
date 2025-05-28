#include "../includes/miniRT.h"

//Ray_Maker
/*
    vou tentar criar um raio
*/

/// @brief Will store the values of the ray
/// @param cords 
/// @param vector3 
/// @return 0 in sucess
void init_ray(t_ray *ray)
{
    ray->cords[0] = 0;
    ray->cords[1] = 0;
    ray->cords[2] = 0;

    ray->vec3[0] = 0;
    ray->vec3[1] = 1;
    ray->vec3[2] = 0;

}

void ray(t_ray ray,cord cord[3] ,vec3 vector[3])
{
    ray.cords[0] = cord[0];
    ray.cords[1] = cord[1];
    ray.cords[2] = cord[2];

    ray.vec3[0] = vector[0];
    ray.vec3[1] = vector[1];
    ray.vec3[2] = vector[2];
}

void init_camera(t_ray *camera)
{


    camera->vec3[0] = 0;
    camera->vec3[1] = 1;
    camera->vec3[2] = 0;

}

/*
    Isto vai me dat t
    A minda ideia vai ser pegar no array e usalo para criar um novo raio pois ja obtenho as coordenadas da colisao(result)
*/

/// @brief  Funcao vai 
/// @param t 
/// @param ray 
/// @param result array que vai guardar as coordenadas da colisao 
void at(double t, t_ray ray, double result[3])
{
    result[0] = ray.cords[0] + t * ray.vec3[0];
    result[1] = ray.cords[1] + t * ray.vec3[1];
    result[2] = ray.cords[2] + t * ray.vec3[2];
}

int write_color(double r, double g, double b) {
	int ir = (int)(255.999 * r);
	int ig = (int)(255.999 * g);
	int ib = (int)(255.999 * b);
	return (ir << 16) | (ig << 8) | ib;
}

void normalize_vec(double out[3], const double v[3]) {
    double len = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
    if (len == 0.0)
        vec3_set(out, 0, 0, 0); // evitar divisão por zero
    else
        vec3_scale(out, v, 1.0 / len);
}



bool hit_sphere( const double center[3],double radius, const t_ray *r)
{
    double oc[3];
    vec3_sub(oc,r->cords,center); 

    double a;
    double b;
    double c;
    double discriminant;

    a = vec3_dot(r->vec3,r->vec3);
    b = 2.0 * vec3_dot(r->vec3,oc);
    c = vec3_dot(oc,oc) - radius * radius;
    discriminant = b * b - 4 *a *c;

    return (discriminant >= 0);
}

void ray_color(const t_ray *ray, double out_color[3]) {

        double sphere_center[3] = {0.0, 0.0, -1.0};
    double sphere_radius = 0.5;

    // Se o raio colidir com a esfera, retorna vermelho
    if (hit_sphere(sphere_center, sphere_radius, ray)) {
        out_color[0] = 1.0;  // R
        out_color[1] = 0.0;  // G
        out_color[2] = 0.0;  // B
        return;
    }

    double unit_direction[3];
    normalize_vec(unit_direction, ray->vec3);

    double a = 0.5 * (unit_direction[1] + 1.0); // y() + 1.0

    // Cores: white = (1,1,1), blue = (0.5, 0.7, 1.0)
    double white[3] = {1.0, 1.0, 1.0};
    double blue[3] = {0.5, 0.7, 1.0};
    double scaled_white[3], scaled_blue[3];

    vec3_scale(scaled_white, white, 1.0 - a);
    vec3_scale(scaled_blue, blue, a);
    vec3_add(out_color, scaled_white, scaled_blue);
}

/*
bool hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = center - r.origin();
    auto a = dot(r.direction(), r.direction());
    auto b = -2.0 * dot(r.direction(), oc);
    auto c = dot(oc, oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;
    return (discriminant >= 0);
}
*/



int main(void)
{
    void *mlx;
    void *mlx_win;
  
    double aspect_ratio = 16.0 / 9.0;
    int image_width = 1080;
    int image_height = (int)(image_width / aspect_ratio);
    if (image_height < 1)
        image_height = 1;

    double focal_length = 1.0;
    double viewport_height = 2.0;
    double viewport_width = viewport_height * ((double)image_width / image_height);

    // Vetores
    double camera_center[3];
    double viewport_v[3];
    double viewport_u[3];
    vec3_set(camera_center, 0, 0, 0);
    vec3_set(viewport_u, viewport_width, 0, 0);
    vec3_set(viewport_v, 0, -viewport_height, 0);

    // Pixel delta
    double pixel_delta_u[3]; vec3_scale(pixel_delta_u, viewport_u, 1.0 / image_width);
    double pixel_delta_v[3]; vec3_scale(pixel_delta_v, viewport_v, 1.0 / image_height);

// viewport_upper_left = camera_center - (0,0,focal_length) - viewport_u/2 - viewport_v/2
    double offset[3];
    double temp1[3], temp2[3], temp3[3], viewport_upper_left[3];
     vec3_set(offset, 0, 0, focal_length);
    vec3_sub(temp1, camera_center, offset);

    vec3_scale(temp2, viewport_u, 0.5);
    vec3_sub(temp1, temp1, temp2);

    vec3_scale(temp3, viewport_v, 0.5);
    vec3_sub(viewport_upper_left, temp1, temp3);

    // pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v)
    double temp4[3], temp5[3], pixel00_loc[3];
    vec3_add(temp4, pixel_delta_u, pixel_delta_v);
    vec3_scale(temp5, temp4, 0.5);
    vec3_add(pixel00_loc, viewport_upper_left, temp5);



    ft_printf("MiniRT Starting...\n");

    mlx = mlx_init();
    if (!mlx)
    {
        ft_printf("Error: Could not initialize MLX\n");
        return (1);
    }

    mlx_win = mlx_new_window(mlx, image_height, image_width, "miniRT");
    if (!mlx_win)
    {

        ft_printf("Error: Could not create window\n");
        return (1);
    }

    int j = 0;
    while (image_width >= j)
    {

        int i = 0;

        while (image_height >= i)
        {
                    // Criação do raio
        t_ray r;
        double scaled_u[3], scaled_v[3], pixel_center[3];
        vec3_scale(scaled_u, pixel_delta_u, j);
        vec3_scale(scaled_v, pixel_delta_v, i);

        double temp_sum[3]; 
        vec3_add(temp_sum, pixel00_loc, scaled_u);
        vec3_add(pixel_center, temp_sum, scaled_v);

        // ray_direction = pixel_center - camera_center
        double ray_direction[3];
        vec3_sub(ray_direction, pixel_center, camera_center);


        vec3_copy(r.cords, camera_center);
        vec3_copy(r.vec3, ray_direction);

        double color[3];
        ray_color(&r, color);

		int rgb = write_color(color[0], color[1], color[2]);
		mlx_pixel_put(mlx, mlx_win, i, j, rgb);
        i++;
        }

        j++;
    }

    ft_printf("Render Completed\n");
    mlx_loop(mlx);

    return (0);
}
