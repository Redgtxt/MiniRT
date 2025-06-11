#include "../../includes/miniRT.h"




/// @brief Will store the values of the ray
/// @param cords 
/// @param vector3 
/// @return 
void init_ray(t_ray *ray)
{
    ray->origin[0] = 0;
    ray->origin[1] = 0;
    ray->origin[2] = 0;

    ray->direction[0] = 0;
    ray->direction[1] = 1;
    ray->direction[2] = 0;

}

//vou dar a informacao para criar um novo raio
/// @brief Create a ray with specific origin and direction (constructor with parameters)
/// @param ray pointer to ray structure
/// @param origin origin point coordinates
/// @param direction direction vector
void create_ray(t_ray *ray, const double origin[3], const double direction[3])
{
    vec3_copy(ray->origin, origin);
    vec3_copy(ray->direction, direction);
}

void sample_square(double out[3])
{
    out[0] = random_double_0_to_1() - 0.5;
    out[1] = random_double_0_to_1() - 0.5;
    out[2] = 0,0;
}

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
    if(ANTIALIASING)
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

/// @brief Get ray origin (equivalent to origin() method)
/// @param ray pointer to ray structure
/// @param out output array to store origin
void ray_origin(const t_ray *ray, double out[3])
{
    vec3_copy(out, ray->origin);
}

/// @brief Get ray direction (equivalent to direction() method)
/// @param ray pointer to ray structure
/// @param out output array to store direction
void ray_direction(const t_ray *ray, double out[3])
{
    vec3_copy(out, ray->direction);
}

void ray_color(t_control_panel *control_panel, const t_ray *ray, double out_color[3])
{
    t_hit_record record;
    double unit_direction[3];
    double white[3] = {1.0, 1.0, 1.0};
    double blue[3] = {0.5, 0.7, 1.0};
    double temp[3];
       
    if (hit_world(control_panel, ray, interval_create(0.001, D_INFINITY), &record))
    {
        // Map normal to color
        out_color[0] = 0.5 * (record.normal[0] + 1.0);
        out_color[1] = 0.5 * (record.normal[1] + 1.0);
        out_color[2] = 0.5 * (record.normal[2] + 1.0);
        return;
    }
    
    // Background - gradient from white to blue
    vec3_normalize(unit_direction, ray->direction);
    double a = 0.5 * (unit_direction[1] + 1.0);
    
    // Calculate (1.0-a)*white + a*blue
    vec3_scale(out_color, white, 1.0 - a);
    vec3_scale(temp, blue, a);
    vec3_add(out_color, out_color, temp);
}