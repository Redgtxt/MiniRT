#include "../../includes/miniRT.h"

/*
    Entao vou calcular primeira as duas caps do cilindro
    depois disso so preciso de calcular o corpo pois o corpo esta entre ambas as partes
*/

/*
FUNCAO Generica que vai ver se estou a bater em uma cap de algum objeto
*/
// bool intersect_cap(
//     t_ray ray,
//     const double cap_center[3],
//     const double cap_normal[3], // deve estar normalizado
//     double cap_radius,
//     double *t_out)
// {
//     double sub[3];
//     double denom = vec3_dot(ray.direction, cap_normal);
//     if (fabs(denom) < 1e-6)
//         return false; // paralelo ao plano

//     vec3_sub(sub, cap_center, ray.origin);
//     double numer = vec3_dot(sub, cap_normal);
//     double t = numer / denom;
//     if (t <= 0)
//         return false; // só consideramos à frente da origem

//     // ponto de interseção
//     double P[3];
//     vec3_add_scaled(ray.origin, ray.direction, t, P);

//     // testa se está dentro do círculo
//     double v[3];
//     vec3_sub(P, cap_center, v);
//     if (vec3_dot(v, v) <= cap_radius * cap_radius)
//     {
//         *t_out = t;
//         return true;
//     }
//     return false;
// }

// bool intersect_cylinder_caps(
//     t_ray ray,
//     const t_cylinder *cyl,
//     t_hit_record *rec)
// {
//     double axis[3];
//     double cap1_center[3];
//     vec3_copy(axis, cyl->vec3);
//     vec3_copy(cap1_center, cyl->cords);
//     double cap2_center[3];
//     vec3_add_scaled(cap1_center, axis, cyl->height, cap2_center);

//     double t_cap;
//     bool hit_anything = false;

//     // Bottom cap (base)
//     if (intersect_cap(ray, cap1_center, axis, cyl->radius, &t_cap) && t_cap < rec->t)
//     {
//         rec->t = t_cap;
//         vec3_copy(rec->normal, axis);
//         vec3_negate(rec->normal, rec->normal); // Normal points outward from cylinder
//         vec3_add_scaled(ray.origin, ray.direction, t_cap, rec->position);
//         rec->material = (t_material *)&cyl->material;
//         rec->front_face = (vec3_dot(ray.direction, rec->normal) < 0);
//         hit_anything = true;
//     }

//     // Top cap
//     if (intersect_cap(ray, cap2_center, axis, cyl->radius, &t_cap) && t_cap < rec->t)
//     {
//         rec->t = t_cap;
//         vec3_copy(rec->normal, axis); // Normal points outward from cylinder
//         vec3_add_scaled(ray.origin, ray.direction, t_cap, rec->position);
//         rec->material = (t_material *)&cyl->material;
//         rec->front_face = (vec3_dot(ray.direction, rec->normal) < 0);
//         hit_anything = true;
//     }

//     return hit_anything;
// }

// static bool solve_quadratic(double a, double b, double c, double *t0, double *t1)
// {
//     double disc = b * b - 4 * a * c;
//     if (disc < 0)
//         return false;
//     double sqrt_d = sqrt(disc);
//     double q = (b < 0) ? (-b - sqrt_d) / 2 : (-b + sqrt_d) / 2;
//     *t0 = q / a;
//     *t1 = c / q;
//     if (*t0 > *t1)
//     {
//         double tmp = *t0;
//         *t0 = *t1;
//         *t1 = tmp;
//     }
//     return true;
// }

// bool intersect_cylinder_body(t_ray ray, const t_cylinder *cyl, t_hit_record *rec)
// {
//     double A[3]; // eixo normalizado
//     double C[3];
//     double O[3];
//     double D[3];

//     vec3_copy(O, ray.origin);
//     vec3_copy(D, ray.direction);
//     vec3_copy(C, cyl->cords); // centro da base
//     vec3_copy(A, cyl->vec3);

//     double OC[3];
//     vec3_sub(OC, O, C);

//     // D_perp = D - dot(D, A) * A
//     double D_dot_A = vec3_dot(D, A);
//     double Dp[3];
//     double tmp[3];
//     vec3_scale(tmp, A, D_dot_A);
//     vec3_sub(Dp, D, tmp);

//     // OC_perp = OC - dot(OC, A) * A
//     double OC_dot_A = vec3_dot(OC, A);
//     double OCp[3];
//     vec3_scale(tmp, A, OC_dot_A);
//     vec3_sub(OCp, OC, tmp);

//     // A, B, C da equação quadrática
//     double a = vec3_dot(Dp, Dp);
//     double b = 2 * vec3_dot(Dp, OCp);
//     double c = vec3_dot(OCp, OCp) - cyl->radius * cyl->radius;

//     double t0, t1;
//     if (!solve_quadratic(a, b, c, &t0, &t1))
//         return false;

//     // seleciona o menor t positivo dentro da altura do cilindro
//     double t_candidate = -1;

//     for (int i = 0; i < 2; i++)
//     {
//         double t = (i == 0) ? t0 : t1;
//         if (t < 1e-6 || t >= rec->t)
//             continue;

//         double P[3];
//         vec3_add_scaled(O, D, t, P);

//         double v[3];
//         vec3_sub(v, P, C);
//         double y = vec3_dot(v, A);

//         if (y >= 0 && y <= cyl->height)
//         {
//             t_candidate = t;
//             break;
//         }
//     }

//     if (t_candidate == -1)
//         return false;

//     // preenche o hit record
//     rec->t = t_candidate;
//     vec3_add_scaled(O, D, t_candidate, rec->position);

//     // normal = (P - C) - proj. no eixo
//     double v[3];
//     vec3_sub(v, rec->position, C);
//     double proj = vec3_dot(v, A);
//     double proj_vec[3];
//     vec3_scale(proj_vec, A, proj);
//     vec3_sub(rec->normal, v, proj_vec);
//     vec3_normalize(rec->normal, rec->normal);

//     // frente ou verso
//     rec->front_face = vec3_dot(D, rec->normal) < 0;
//     if (!rec->front_face)
//         vec3_negate(rec->normal, rec->normal);

//     rec->material = (t_material *)&cyl->material;

//     return true;
// }

// bool have_hit_cylinder(t_cylinder *cyl, const t_ray *ray, t_interval t_ray, t_hit_record *record)
// {
//     (void)t_ray; // Acknowledge unused parameter
//     t_hit_record temp_rec = *record;
//     bool hit_anything = false;

//     // First check if the caps are hit
//     if (intersect_cylinder_caps(*ray, cyl, &temp_rec))
//     {
//         hit_anything = true;
//         *record = temp_rec;
//     }

//     // Then check if the body is hit (potentially closer)
//     // if (intersect_cylinder_body(*ray, cyl, &temp_rec))
//     // {
//     //     hit_anything = true;
//     //     *record = temp_rec;
//     // }

//     return hit_anything;
// }

double pont_dist(vec3 a[3], vec3 b[3])
{
    vec3 res[3];

    vec3_sub(res, a, b);
    return (fabs(vec3_lenght(res)));
}

static bool have_hit_cylinder_cap(t_cylinder *plane, const t_ray *ray, t_interval t_ray, t_hit_record *record)
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

    if (pont_dist(record->position, plane->cords) <= plane->radius)
        return (true);
    return (false);
}

void vec3_add_dir(vec3 original[3], vec3 dir[3], double dist)
{
    original[0] = original[0] + dir[0] * dist;
    original[1] = original[1] + dir[1] * dist;
    original[2] = original[2] + dir[2] * dist;
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
        temp_rec.t = closest_so_far;

        vec3_add_dir(scene->cylinder[i].cords, scene->cylinder[i].vec3, scene->cylinder[i].height / 2);
        if (have_hit_cylinder_cap(&scene->cylinder[i], ray, interval_create(t_ray.min, closest_so_far), &temp_rec))
        {
            if (temp_rec.t < closest_so_far)
            {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                *record = temp_rec;
            }
        }
        vec3_add_dir(scene->cylinder[i].cords, scene->cylinder[i].vec3, scene->cylinder[i].height * -1);
        if (have_hit_cylinder_cap(&scene->cylinder[i], ray, interval_create(t_ray.min, closest_so_far), &temp_rec))
        {
            if (temp_rec.t < closest_so_far)
            {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                *record = temp_rec;
            }
        }
        vec3_add_dir(scene->cylinder[i].cords, scene->cylinder[i].vec3, scene->cylinder[i].height / 2);
        i++;
    }
    return hit_anything;
}