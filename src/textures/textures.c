#include "../../includes/miniRT.h"

//	LAMBERTIAN MATERIAL
bool lambertian_scatter(t_hit_record *rec, t_data_scatter *data_scatter)
{
    double scatter_direction[3];

    // Generate a random direction in the same hemisphere as the surface normal
    random_on_hemisphere(rec->normal, scatter_direction);

    // Handle degenerate scatter direction (very close to zero)
    if (vec3_near_zero(scatter_direction))
    {
        vec3_copy(scatter_direction, rec->normal);
    }

    // Create the scattered ray: origin at hit point, direction = scatter direction
    create_ray(&data_scatter->scattered, rec->position, scatter_direction);

    // Attenuation is simply the material's albedo (color)
    vec3_copy(data_scatter->attenuation, rec->material->albedo);

    return true;
}
//	-------------------	//

//	METAL MATERIAL
void reflect(const double v[3], const double n[3], double out[3])
{
    double dot_vn = vec3_dot(v, n); // dot(v, n)
    double scaled_normal[3];

    vec3_scale(scaled_normal, n, 2.0 * dot_vn); // 2 * dot(v, n) * n
    vec3_sub(out, v, scaled_normal);            // out = v - 2 * dot(v,n) * n
}

bool metal_scatter(const t_ray *r_in, t_hit_record *rec, t_data_scatter *data_scatter)
{
    double reflected[3];
    reflect(r_in->direction, rec->normal, reflected);

    create_ray(&data_scatter->scattered, rec->position, reflected);
    vec3_copy(data_scatter->attenuation, rec->material->albedo);

    // Only reflect if the ray is in the same hemisphere as the surface normal
    return (vec3_dot(data_scatter->scattered.direction, rec->normal) > 0);
}
//	------------------	//

// CHECKERPATTERN MATERIAL
bool checker_scatter(t_hit_record *rec, t_data_scatter *data_scatter)
{
    double scatter_direction[3];
    double checker_color[3];
    double scale = rec->material->checker_scale;

    if (scale <= 0)
        scale = 1.0; // Default scale if not set

    // Generate a scatter direction (like lambertian)
    random_on_hemisphere(rec->normal, scatter_direction);

    if (vec3_near_zero(scatter_direction))
        vec3_copy(scatter_direction, rec->normal);

    create_ray(&data_scatter->scattered, rec->position, scatter_direction);

    // Determine checker pattern color
    int x = floor(rec->position[0] / scale);
    int y = floor(rec->position[1] / scale);
    int z = floor(rec->position[2] / scale);

    // Check if the sum of coordinates is even or odd
    if ((x + y + z) % 2 == 0)
    {
        // Use the albedo color for even squares
        vec3_copy(checker_color, rec->material->albedo);
    }
    else
    {
        // Use a contrasting color (inverse or black) for odd squares
        checker_color[0] = rec->material->albedo[0] * 0.2;
        checker_color[1] = rec->material->albedo[1] * 0.2;
        checker_color[2] = rec->material->albedo[2] * 0.2;
    }

    vec3_copy(data_scatter->attenuation, checker_color);
    return true;
}


bool scatter(const t_material *mat, const t_ray *r_in, t_hit_record *rec, t_data_scatter *data_scatter)
{
    if (mat->type == LAMBERTIAN)
        return lambertian_scatter(rec, data_scatter);
    else if (mat->type == METAL)
        return metal_scatter(r_in, rec, data_scatter);
    else if (mat->type == CHECKERPATTERN)
        return checker_scatter(rec, data_scatter);
    // else if (mat->type == DIELECTRIC)
    //     return dielectric_scatter(mat, r_in, rec, attenuation, scattered);
    return false;
}