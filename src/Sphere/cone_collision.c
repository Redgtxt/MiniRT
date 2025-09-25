#include "../../includes/miniRT.h"

/*
    For a cone, we'll need to:
    1. Check for intersection with the base cap
    2. Check for intersection with the cone body
    3. Combine the results to find the closest intersection
*/


// Function to check if a ray hits the base cap of a cone
static bool have_hit_cone_cap(t_cone *cone, const t_ray *ray, t_interval t_ray, t_hit_record *record)
{
	double cap_center[3];
	double p_minus_o[3];
	double intersection_point[3];
	double dist_vec[3];
	double denom;
	double t;

	vec3_add_scaled(cap_center, cone->cords, cone->vec3, -cone->height / 2.0);
	denom = vec3_dot(cone->vec3, ray->direction);
	if (fabs(denom) < 1e-8)
		return (false);
	vec3_sub(p_minus_o, cap_center, ray->origin);
	t = vec3_dot(p_minus_o, cone->vec3) / denom;
	if (!interval_contains(t,t_ray))
		return (false);
	ray_at(t, *ray, intersection_point);
	vec3_sub(dist_vec, intersection_point, cap_center);
	if (vec3_length(dist_vec) > cone->radius)
		return (false);
	record->t = t;
	ray_at(t, *ray, record->position);
	vec3_negate(record->normal, cone->vec3);
	record->material = &cone->material;
	return (true);
}

// Function to check if a ray hits the body of a cone
static bool hit_cone_body(t_cone *cone, const t_ray *ray, t_interval t_ray, t_hit_record *record)
{
	double oc[3];
	double tan_theta;
	double k;
	double dot_d_v;
	double dot_oc_v;
	double a;
	double b;
	double c;
	double discriminant;
	double sqrt_d;
	double t1;
	double t2;
	double t;
	double m1;
	double m2;
	double m;
	double temp[3];
	double normal[3];
	double p_minus_c[3];
	double cone_tip[3];

	// Calculate the tip of the cone (cone->cords + height/2 * axis)
	vec3_add_scaled(cone_tip, cone->cords, cone->vec3, cone->height / 2.0);
	vec3_sub(oc, ray->origin, cone_tip);
	tan_theta = cone->radius / cone->height;
	k = tan_theta * tan_theta;
	dot_d_v = vec3_dot(ray->direction, cone->vec3);
	dot_oc_v = vec3_dot(oc, cone->vec3);
	a = vec3_dot(ray->direction, ray->direction) - (1 + k) * dot_d_v * dot_d_v;
	b = 2 * (vec3_dot(ray->direction, oc) - (1 + k) * dot_d_v * dot_oc_v);
	c = vec3_dot(oc, oc) - (1 + k) * dot_oc_v * dot_oc_v;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (false);
	sqrt_d = sqrt(discriminant);
	t1 = (-b - sqrt_d) / (2 * a);
	t2 = (-b + sqrt_d) / (2 * a);
	t = -1;
	m1 = dot_d_v * t1 + dot_oc_v;
	if (interval_contains(t1,t_ray) && m1 < 0 && m1 > -cone->height)
		t = t1;
	m2 = dot_d_v * t2 + dot_oc_v;
	if (interval_contains(t2,t_ray) && m2 < 0 && m2 > -cone->height)
	{
		if (t < 0 || t2 < t)
			t = t2;
	}
	if (t < 0)
		return (false);
	record->t = t;
	ray_at(t, *ray, record->position);
	m = dot_d_v * t + dot_oc_v;
	vec3_scale(temp, cone->vec3, m * (1 + k));
	vec3_sub(p_minus_c, record->position, cone_tip);
	vec3_sub(normal, p_minus_c, temp);
	vec3_normalize(record->normal, normal);
	record->material = &cone->material;
	return (true);
}

// Main function to check for intersection with a cone (body and cap)
bool have_hit_cone(t_cone *cone, const t_ray *ray, t_interval t_ray, t_hit_record *record)
{
	bool hit_anything;
	double closest_so_far;
	t_hit_record temp_rec;
	t_cone original_cone;

	original_cone = *cone;
	hit_anything = false;
	closest_so_far = t_ray.max;
	vec3_normalize(cone->vec3, cone->vec3);
	if (hit_cone_body(cone, ray, interval_create(t_ray.min, closest_so_far), &temp_rec))
	{
		hit_anything = true;
		closest_so_far = temp_rec.t;
		*record = temp_rec;
	}
	if (have_hit_cone_cap(cone, ray, interval_create(t_ray.min, closest_so_far), &temp_rec))
	{
		hit_anything = true;
		closest_so_far = temp_rec.t;
		*record = temp_rec;
	}
	*cone = original_cone;
	return (hit_anything);
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
