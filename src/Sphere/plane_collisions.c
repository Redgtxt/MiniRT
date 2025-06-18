#include "../../includes/miniRT.h"

static bool have_hit_plane(t_plane *plane, const t_ray *ray, t_interval t_ray, t_hit_record *record)
{
    double denom;
    double p0l0[3];
    double t;

    // Calcular o produto escalar entre o vetor normal do plano e a direção do raio
    denom = vec3_dot(plane->vec3, ray->direction);

    // Se o produto é próximo de zero, o raio é paralelo ao plano (não há interseção)
    if (fabs(denom) < 0.0001)
        return false;

    // Calcular o vetor do ponto do raio ao ponto do plano
    vec3_sub(p0l0, plane->cords, ray->origin);

    // Calcular a distância até o ponto de interseção
    t = vec3_dot(p0l0, plane->vec3) / denom;

    // Verificar se a interseção está no intervalo válido
    if (!interval_surrounds(t, t_ray))
        return false;

    // Registrar a interseção
    record->t = t;

    // Calcular o ponto de colisão
    ray_at(record->t, *ray, record->position);

    // Para planos, a normal é o próprio vetor normal do plano (normalizado)
    double outward_normal[3];
    vec3_copy(outward_normal, plane->vec3);
    vec3_normalize(outward_normal, outward_normal);

    // Definir o lado da face
    set_face_normal(ray, outward_normal, record);
    record->material = &plane->material;

    return true;
}

bool hit_planes(t_control_panel *scene, const t_ray *ray, t_interval t_ray, t_hit_record *record)
{
    bool hit_anything = false;
    double closest_so_far = t_ray.max;
    t_hit_record temp_rec;

    size_t i = 0;
    while (i < scene->data.plane_count)
    {
        if (have_hit_plane(&scene->plane[i], ray, interval_create(t_ray.min, closest_so_far), &temp_rec))
        {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            *record = temp_rec; // Copia o registro do hit mais próximo
        }
        i++;
    }

    return hit_anything;
}
