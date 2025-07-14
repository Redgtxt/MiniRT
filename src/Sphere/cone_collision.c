#include "../../includes/miniRT.h"

/*
    For a cone, we'll need to:
    1. Check for intersection with the base cap
    2. Check for intersection with the cone body
    3. Combine the results to find the closest intersection
*/

// This function checks if a ray hits the body of a cone
static bool hit_cone_body(t_cone *cone, const t_ray *ray, t_interval t_ray, t_hit_record *record)
{
    // Normalize the cone axis
    vec3 axis[3];
    vec3_copy(axis, cone->vec3);
    vec3_normalize(axis, axis);

    // Calculate base center and apex positions
    vec3 base_center[3];
    vec3 apex[3];
    
    // Base is at cone->cords, apex is at the top
    vec3_copy(base_center, cone->cords);
    vec3_copy(apex, cone->cords);
    vec3_add_dir(apex, axis, cone->height);
    
    // Vector from apex to ray origin
    vec3 oc[3];
    vec3_sub(oc, ray->origin, apex);

    // Calculate cone angle - ENSURE radius is diameter/2
    double radius = cone->d / 2.0;  // Use diameter/2 for radius
    double tan_theta_sq = (radius * radius) / (cone->height * cone->height);

    // Calculate quadratic equation coefficients for cone intersection
    double dot_dir_axis = vec3_dot(ray->direction, axis);
    double dot_oc_axis = vec3_dot(oc, axis);
    
    // Corrected quadratic coefficients
    double a = vec3_dot(ray->direction, ray->direction) - (1.0 + tan_theta_sq) * dot_dir_axis * dot_dir_axis;
    double b = 2.0 * (vec3_dot(ray->direction, oc) - (1.0 + tan_theta_sq) * dot_dir_axis * dot_oc_axis);
    double c = vec3_dot(oc, oc) - (1.0 + tan_theta_sq) * dot_oc_axis * dot_oc_axis;

    // Solve quadratic equation
    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return false;

    // Find valid intersection
    double sqrt_disc = sqrt(discriminant);
    double t1 = (-b - sqrt_disc) / (2 * a);
    double t2 = (-b + sqrt_disc) / (2 * a);

    // Test both solutions
    double t = t1;
    if (t < t_ray.min || t > t_ray.max)
    {
        t = t2;
        if (t < t_ray.min || t > t_ray.max)
            return false;
    }

    // Calculate hit position
    vec3 hit_point[3];
    ray_at(t, *ray, hit_point);

    // Check if hit point is within cone height
    vec3 hit_to_apex[3];
    vec3_sub(hit_to_apex, hit_point, apex);
    double height_from_apex = vec3_dot(hit_to_apex, axis);
    
    // Height should be between 0 (at apex) and -cone->height (at base)
    if (height_from_apex > 0 || height_from_apex < -cone->height)
        return false;

    // Valid hit - record details
    record->t = t;
    vec3_copy(record->position, hit_point);

    // Calculate normal at hit point
    double height_from_base = -height_from_apex;

    // Find point on axis at same height as hit point
    vec3 axis_point[3];
    vec3_copy(axis_point, cone->cords);
    vec3_add_dir(axis_point, axis, height_from_base);

    // Vector from axis point to hit point (radial direction)
    vec3 radial[3];
    vec3_sub(radial, hit_point, axis_point);
    vec3_normalize(radial, radial);

    // Calculate cone surface normal
    vec3 outward_normal[3];
    double slope_factor = radius / cone->height;

    // Combine radial and axial components
    vec3_scale(outward_normal, radial, 1.0); // Radial component
    vec3 axial_component[3];
    vec3_scale(axial_component, axis, slope_factor); // Axial component
    vec3_add(outward_normal, outward_normal, axial_component);
    vec3_normalize(outward_normal, outward_normal);

    // Ensure the normal points outward
    set_face_normal(ray, outward_normal, record);
    record->material = &cone->material;

    return true;
}

// For the cone cap (base only)
static bool have_hit_cone_cap(t_cone *cone, const t_ray *ray, t_interval t_ray, t_hit_record *record)
{
    // Normalize the axis vector
    vec3 normalized_axis[3];
    vec3_copy(normalized_axis, cone->vec3);
    vec3_normalize(normalized_axis, normalized_axis);

    // The cap's normal should point OUTWARD from the cone, so it's the NEGATIVE of the axis vector.
    vec3 cap_normal[3];
    vec3_negate(cap_normal, normalized_axis);

    // Calculate the dot product between the cap normal and ray direction
    double denom = vec3_dot(ray->direction, cap_normal);

    // If close to zero, ray is parallel to the cap
    if (fabs(denom) < 1e-6)
        return false;

    // Vector from ray origin to cap center (cone->cords is the BASE center)
    vec3 p0l0[3];
    vec3_sub(p0l0, cone->cords, ray->origin);

    // Calculate distance to intersection
    double t = vec3_dot(p0l0, cap_normal) / denom;

    // Check if intersection is in valid range
    if (!interval_surrounds(t, t_ray))
        return false;

    // Calculate collision point
    vec3 hit_point[3];
    ray_at(t, *ray, hit_point);

    // Check if hit point is within the cap's radius
    double radius = cone->d / 2.0;  // Use diameter/2 for radius
    if (pont_dist(hit_point, cone->cords) > radius)
        return false;

    // Record the intersection
    record->t = t;
    vec3_copy(record->position, hit_point);

    // Set the face normal using the correct outward-pointing cap normal
    set_face_normal(ray, cap_normal, record);
    record->material = &cone->material;

    return true;
}

// Main cone intersection function
bool have_hit_cone(t_cone *cone, const t_ray *ray, t_interval t_ray, t_hit_record *record)
{
    bool hit_anything = false;
    double closest_so_far = t_ray.max;
    t_hit_record temp_rec;

    // Check cone body first
    if (hit_cone_body(cone, ray, interval_create(t_ray.min, closest_so_far), &temp_rec))
    {
        hit_anything = true;
        closest_so_far = temp_rec.t;
        *record = temp_rec;
    }

    // Check base cap second (this should override body if closer)
    if (have_hit_cone_cap(cone, ray, interval_create(t_ray.min, closest_so_far), &temp_rec))
    {
        hit_anything = true;
        closest_so_far = temp_rec.t;
        *record = temp_rec;
    }

    return hit_anything;
}

// Function to check all cones in the scene
bool hit_cones(t_control_panel *scene, const t_ray *ray, t_interval t_ray, t_hit_record *record)
{
    bool hit_anything = false;
    double closest_so_far = t_ray.max;
    t_hit_record temp_rec;

    size_t i = 0;
    while (i < scene->data.cone_count)
    {
        if (have_hit_cone(&scene->cone[i], ray, interval_create(t_ray.min, closest_so_far), &temp_rec))
        {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            *record = temp_rec;
        }
        i++;
    }

    return hit_anything;
}
