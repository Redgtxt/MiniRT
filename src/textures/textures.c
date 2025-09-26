#include "../../includes/miniRT.h"

//	LAMBERTIAN MATERIAL
bool lambertian_scatter(t_hit_record *rec, t_data_scatter *data_scatter)
{
    double scatter_direction[3];

    random_on_hemisphere(rec->normal, scatter_direction);
    if (vec3_near_zero(scatter_direction))
        vec3_copy(scatter_direction, rec->normal);
    create_ray(&data_scatter->scattered, rec->position, scatter_direction);
    vec3_copy(data_scatter->attenuation, rec->material->albedo);
    return true;
}
//	-------------------	//

//	METAL MATERIAL
bool metal_scatter(const t_ray *r_in, t_hit_record *rec, t_data_scatter *data_scatter)
{
    double reflected[3];

    reflect(r_in->direction, rec->normal, reflected);
    create_ray(&data_scatter->scattered, rec->position, reflected);
    vec3_copy(data_scatter->attenuation, rec->material->albedo);
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
        scale = 1.0;
    random_on_hemisphere(rec->normal, scatter_direction);
    if (vec3_near_zero(scatter_direction))
        vec3_copy(scatter_direction, rec->normal);
    create_ray(&data_scatter->scattered, rec->position, scatter_direction);
    int x = floor(rec->position[0] / scale);
    int y = floor(rec->position[1] / scale);
    int z = floor(rec->position[2] / scale);
    if ((x + y + z) % 2 == 0)
        vec3_copy(checker_color, rec->material->albedo);
    else
    {
        checker_color[0] = rec->material->albedo[0] * 0.2;
        checker_color[1] = rec->material->albedo[1] * 0.2;
        checker_color[2] = rec->material->albedo[2] * 0.2;
    }
    vec3_copy(data_scatter->attenuation, checker_color);
    return true;
}

//	GLASS MATERIAL
bool glass_scatter(const t_ray *r_in, t_hit_record *rec, t_data_scatter *data_scatter)
{
    double unit_direction[3];
    double cos_theta;
    double sin_theta;
    double ri;
    bool cannot_refract;
    double direction[3];

    vec3_set(data_scatter->attenuation, 1.0, 1.0, 1.0);
    ri = rec->front_face ? (1.0 / rec->material->refraction_index) : rec->material->refraction_index;
    vec3_unit_vector(unit_direction, r_in->direction);
    double neg_unit_direction[3];
    vec3_negate(neg_unit_direction, unit_direction);
    cos_theta = vec3_dot(neg_unit_direction, rec->normal);
    if (cos_theta > 1.0)
        cos_theta = 1.0;
    sin_theta = sqrt(1.0 - cos_theta * cos_theta);
    cannot_refract = ri * sin_theta > 1.0;
    if (cannot_refract || schlick_reflectance(cos_theta, ri) > random_double_0_to_1())
        reflect(unit_direction, rec->normal, direction);
    else
        refract(unit_direction, rec->normal, ri, direction);
    create_ray(&data_scatter->scattered, rec->position, direction);
    return true;
}

//	------------------	//

bool scatter(const t_material *mat, const t_ray *r_in, t_hit_record *rec, t_data_scatter *data_scatter)
{
    if (mat->type == LAMBERTIAN)
        return lambertian_scatter(rec, data_scatter);
    else if (mat->type == METAL)
        return metal_scatter(r_in, rec, data_scatter);
    else if (mat->type == CHECKERPATTERN)
        return checker_scatter(rec, data_scatter);
    else if (mat->type == GLASS)
        return glass_scatter(r_in, rec, data_scatter);
    return false;
}