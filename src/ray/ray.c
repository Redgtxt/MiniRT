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

// vou dar a informacao para criar um novo raio
/// @brief Create a ray with specific origin and direction (constructor with parameters)
/// @param ray pointer to ray structure
/// @param origin origin point coordinates
/// @param direction direction vector
void create_ray(t_ray *ray, const double origin[3], const double direction[3])
{
    vec3_copy(ray->origin, origin);
    vec3_copy(ray->direction, direction);
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

bool lambertian_scatter(t_hit_record *rec, double attenuation[3], t_ray *scattered) {
    double scatter_direction[3];

    // Generate a random direction in the same hemisphere as the surface normal
    random_on_hemisphere(rec->normal, scatter_direction);

    // Handle degenerate scatter direction (very close to zero)
    if (vec3_near_zero(scatter_direction)) {
        vec3_copy(scatter_direction, rec->normal);
    }

    // Create the scattered ray: origin at hit point, direction = scatter direction
    create_ray(scattered, rec->position, scatter_direction);

    // Attenuation is simply the material's albedo (color)
    vec3_copy(attenuation, rec->material->albedo);

    return true;
}

bool scatter(const t_material *mat, t_hit_record *rec, double attenuation[3], t_ray *scattered)
{
    if (mat->type == LAMBERTIAN)
        return lambertian_scatter(rec, attenuation, scattered);
    // else if (mat->type == METAL)
    //     return metal_scatter(mat, r_in, rec, attenuation, scattered);
    // else if (mat->type == DIELECTRIC)
    //     return dielectric_scatter(mat, r_in, rec, attenuation, scattered);
    return false;
}


void ray_color(t_control_panel *control_panel,int depth, const t_ray *ray, double out_color[3])
{
    t_hit_record record;
    double unit_direction[3];
    double white[3] = {1.0, 1.0, 1.0};
    double temp[3];

    // printf("rrrrr\n");
    if (0 >= depth)
    {
        vec3_zero(out_color);
        return;
    }


    if (hit_world(control_panel, ray, interval_create(0.001, D_INFINITY), &record))
    {
        t_ray scattered;
        double attenuation[3];

        if (scatter(record.material, &record, attenuation, &scattered)) {
            double color[3];
            ray_color(control_panel, depth - 1, &scattered, color);
            vec3_multiply(color, color, attenuation); // final_color *= attenuation
            vec3_scale(color, color, control_panel->light.object_brightness); 
            vec3_copy(out_color, color);
            return;
        }
        
        vec3_zero(out_color);
        return;
    }

    // Background - gradient from white to blue
    vec3_normalize(unit_direction, ray->direction);
    double a = 0.5 * (unit_direction[1] + 1.0);

    // Calculate (1.0-a)*white + a*blue
    vec3_scale(out_color, white, control_panel->amb_light.light_force - a);
    vec3_scale(temp, control_panel->amb_light.rgb, a);
    vec3_add(out_color, out_color, temp);
}
