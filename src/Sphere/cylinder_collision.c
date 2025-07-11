#include "../../includes/miniRT.h"

/*
    Entao vou calcular primeira as duas caps do cilindro
    depois disso so preciso de calcular o corpo pois o corpo esta entre ambas as partes
*/

/*
FUNCAO Generica que vai ver se estou a bater em uma cap de algum objeto
*/

// This function checks if a ray hits the body of a cylinder
static bool hit_cylinder_body(t_cylinder *cylinder, const t_ray *ray, t_interval t_ray, t_hit_record *record)
{
    // Normalize the cylinder axis
    vec3 axis[3];
    vec3_copy(axis, cylinder->vec3);
    vec3_normalize(axis, axis);

    // Vector from cylinder base center to ray origin
    vec3 oc[3];
    vec3_sub(oc, ray->origin, cylinder->cords);

    // Calculate components perpendicular to axis
    double dir_dot_axis = vec3_dot(ray->direction, axis);
    double oc_dot_axis = vec3_dot(oc, axis);

    // Calculate perpendicular components
    vec3 dir_parallel[3], dir_perp[3], oc_parallel[3], oc_perp[3];

    vec3_scale(dir_parallel, axis, dir_dot_axis);
    vec3_sub(dir_perp, ray->direction, dir_parallel);

    vec3_scale(oc_parallel, axis, oc_dot_axis);
    vec3_sub(oc_perp, oc, oc_parallel);

    // Quadratic equation coefficients
    double a = vec3_dot(dir_perp, dir_perp);
    double b = 2 * vec3_dot(dir_perp, oc_perp);
    double c = vec3_dot(oc_perp, oc_perp) - cylinder->radius * cylinder->radius;

    // Solve quadratic equation
    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return false;

    double sqrt_disc = sqrt(discriminant);
    double t1 = (-b - sqrt_disc) / (2 * a);
    double t2 = (-b + sqrt_disc) / (2 * a);

    // Find valid intersection point
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

    // Check if hit point is within cylinder height
    vec3 hit_vec[3];
    vec3_sub(hit_vec, hit_point, cylinder->cords);
    double hit_height = vec3_dot(hit_vec, axis);

    // Fix: Check if within [-height/2, height/2] range to match cap positions
    if (hit_height < -cylinder->height / 2 || hit_height > cylinder->height / 2)
        return false;

    // Valid hit - record details
    record->t = t;
    vec3_copy(record->position, hit_point);

    // Calculate normal at hit point
    vec3 cp[3];
    vec3_scale(cp, axis, hit_height);
    vec3_add(cp, cylinder->cords, cp);

    vec3 outward_normal[3];
    vec3_sub(outward_normal, hit_point, cp);
    vec3_normalize(outward_normal, outward_normal);

    set_face_normal(ray, outward_normal, record);
    record->material = &cylinder->material;

    return true;
}

double pont_dist(vec3 a[3], vec3 b[3])
{
    vec3 res[3];

    vec3_sub(res, a, b);
    return (fabs(vec3_lenght(res)));
}

static bool have_hit_cylinder_cap(t_cylinder *cylinder, const t_ray *ray, t_interval t_ray, t_hit_record *record)
{
    double denom;
    double p0l0[3];
    double t;

    // Normalize the axis vector first
    vec3 normalized_axis[3];
    vec3_copy(normalized_axis, cylinder->vec3);
    vec3_normalize(normalized_axis, normalized_axis);

    // Calcular o produto escalar entre o vetor normal do plano e a direção do raio
    denom = vec3_dot(normalized_axis, ray->direction);

    // Se o produto é próximo de zero, o raio é paralelo ao plano (não há interseção)
    if (fabs(denom) < 0.0001)
        return false;

    // Calcular o vetor do ponto do raio ao ponto do plano
    vec3_sub(p0l0, cylinder->cords, ray->origin);

    // Calcular a distância até o ponto de interseção
    t = vec3_dot(p0l0, normalized_axis) / denom;

    // Verificar se a interseção está no intervalo válido
    if (!interval_surrounds(t, t_ray))
        return false;

    // Registrar a interseção
    record->t = t;

    // Calcular o ponto de colisão
    ray_at(record->t, *ray, record->position);

    // Para planos, a normal é o próprio vetor normal do plano (normalizado)
    double outward_normal[3];
    vec3_copy(outward_normal, normalized_axis);

    // Definir o lado da face
    set_face_normal(ray, outward_normal, record);
    record->material = &cylinder->material;

    if (pont_dist(record->position, cylinder->cords) <= cylinder->radius)
        return (true);
    return (false);
}

void vec3_add_dir(vec3 original[3], vec3 dir[3], double dist)
{
    original[0] = original[0] + dir[0] * dist;
    original[1] = original[1] + dir[1] * dist;
    original[2] = original[2] + dir[2] * dist;
}

bool have_hit_cylinder(t_cylinder *cylinder, const t_ray *ray, t_interval t_ray, t_hit_record *record)
{
    bool hit_anything = false;
    double closest_so_far = t_ray.max;
    t_hit_record temp_rec;

    // Save original cylinder data
    t_cylinder original_cylinder = *cylinder;
    double original_rgb[3];
    vec3_copy(original_rgb, cylinder->rgb); // Save original RGB values

    // Normalize the axis
    vec3 normalized_axis[3];
    vec3_copy(normalized_axis, original_cylinder.vec3);
    vec3_normalize(normalized_axis, normalized_axis);

    // Check top cap
    vec3_copy(cylinder->cords, original_cylinder.cords);
    vec3_add_dir(cylinder->cords, normalized_axis, original_cylinder.height / 2);
    vec3_copy(cylinder->vec3, normalized_axis);

    if (have_hit_cylinder_cap(cylinder, ray, interval_create(t_ray.min, closest_so_far), &temp_rec))
    {
        hit_anything = true;
        closest_so_far = temp_rec.t;
        *record = temp_rec;
    }

    // Check bottom cap
    vec3_copy(cylinder->cords, original_cylinder.cords);
    vec3_add_dir(cylinder->cords, normalized_axis, -original_cylinder.height / 2);
    vec3_copy(cylinder->vec3, normalized_axis);

    if (have_hit_cylinder_cap(cylinder, ray, interval_create(t_ray.min, closest_so_far), &temp_rec))
    {
        hit_anything = true;
        closest_so_far = temp_rec.t;
        *record = temp_rec;
    }

    // Reset cylinder to original and check body
    *cylinder = original_cylinder;

    if (hit_cylinder_body(cylinder, ray, interval_create(t_ray.min, closest_so_far), &temp_rec))
    {
        hit_anything = true;
        closest_so_far = temp_rec.t;
        *record = temp_rec;
    }

    // Make sure to restore original cylinder values before returning
    *cylinder = original_cylinder;
    vec3_copy(cylinder->rgb, original_rgb);             // Restore RGB values explicitly
    vec3_copy(cylinder->material.albedo, original_rgb); // Restore material albedo

    return hit_anything;
}

// Function to check all cylinders in the scene
bool hit_cylinders(t_control_panel *scene, const t_ray *ray, t_interval t_ray, t_hit_record *record)
{
    bool hit_anything = false;
    double closest_so_far = t_ray.max;
    t_hit_record temp_rec;

    size_t i = 0;
    while (i < scene->data.cylinder_count)
    {
        if (have_hit_cylinder(&scene->cylinder[i], ray, interval_create(t_ray.min, closest_so_far), &temp_rec))
        {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            *record = temp_rec; // Copy the closest hit record
        }
        i++;
    }

    return hit_anything;
}
