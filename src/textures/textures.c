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

bool scatter(const t_material *mat, const t_ray *r_in, t_hit_record *rec, t_data_scatter *data_scatter)
{
    if (mat->type == LAMBERTIAN)
        return lambertian_scatter(rec, data_scatter);
    else if (mat->type == METAL)
        return metal_scatter(r_in, rec, data_scatter);
    // else if (mat->type == DIELECTRIC)
    //     return dielectric_scatter(mat, r_in, rec, attenuation, scattered);
    return false;
}
