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
    
    // Check for any blocking objects along the path to light
    if (hit_world(panel, &shadow_ray, interval_create(0.001, light_distance), &rec))
    {
        // If we hit a glass object, it should cast a very light shadow
        if (rec.material->type == GLASS)
        {
            // Glass allows most light through but blocks about 10-20%
            // We'll return a probability-based result for subtle shadows
            return (random_double_0_to_1() < 0.15); // 15% chance of shadow
        }
        else
        {
            // Hit an opaque object - we're in full shadow
            return true;
        }
    }
    
    // No objects blocking the light
    return false;
}

// Get shadow intensity (0.0 = full shadow, 1.0 = no shadow)
double get_shadow_intensity(t_control_panel *panel, vec3 point[3], t_light *light)
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
    double light_transmission = 1.0; // Start with full light
    
    // Check for any blocking objects along the path to light
    while (hit_world(panel, &shadow_ray, interval_create(0.001, light_distance), &rec))
    {
        if (rec.material->type == GLASS)
        {
            // Glass transmits about 70-80% of light, blocks 20-30% for more visible shadows
            light_transmission *= 0.75;
            
            // Move ray origin just past the glass surface and continue
            vec3 new_origin[3];
            vec3_scale(new_origin, shadow_ray.direction, 0.002);
            vec3_add(new_origin, new_origin, rec.position);
            create_ray(&shadow_ray, new_origin, light_dir);
            
            // Update remaining distance to light
            vec3 remaining_dir[3];
            vec3_sub(remaining_dir, light->cords, new_origin);
            light_distance = vec3_length(remaining_dir);
            
            // Continue checking for more obstacles
            continue;
        }
        else
        {
            // Hit an opaque object - full shadow
            return 0.0;
        }
    }
    
    return light_transmission;
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
