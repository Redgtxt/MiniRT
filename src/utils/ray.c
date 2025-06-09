#include "../../includes/miniRT.h"


double degrees_to_radians(double degrees)
{
    return degrees * PI / 180.0;
}

/// @brief Will store the values of the ray
/// @param cords 
/// @param vector3 
/// @return 0 in sucess
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