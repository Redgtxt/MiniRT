#include "../../includes/miniRT.h"

bool is_shadowed(t_control_panel *panel, vec3 point[3], t_light *light)
{
    vec3 light_dir[3];
    vec3_sub(light_dir, light->cords, point);
    double light_distance = vec3_length(light_dir);
    vec3_normalize(light_dir, light_dir);

    // Offset origin to prevent self-intersection
    vec3 shadow_origin[3];
    vec3_scale(shadow_origin, light_dir, 0.001);
    vec3_add(shadow_origin, shadow_origin, point);

    t_ray shadow_ray;
    create_ray(&shadow_ray, shadow_origin, light_dir);

    t_hit_record rec;
    return hit_world(panel, &shadow_ray, interval_create(0.001, light_distance), &rec);
}

void	diffuse_comp(t_light *light, t_hit_record *rec, vec3 color[3], vec3 light_dir[3], double attenuation)
{
	double diff = fmax(vec3_dot(rec->normal, light_dir), 0.0);
    vec3 diffuse[3];
    vec3_scale(diffuse, rec->material->albedo, diff * DIFFUSE_INTENSITY);
    vec3_multiply(diffuse, diffuse, light->rgb);
    vec3_scale(diffuse, diffuse, light->brightness * attenuation);
    vec3_add(color, color, diffuse);
}
