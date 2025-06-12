#include "../../includes/miniRT.h"

/*
    CADA ESFERA VAI ESTAR EM UM ARRAY

    TEORICAMENTE VOU TER UM ARRAY DE ESTRUTURAS PARA A ESFERA???


    A MELHOR ALTURA SERIA DEPOIS DE FAZER O PARSING PASSAR LOGO AS LINKED LIST PARA ESTRUTURAS NORMAIS???

    PARA CONSEGUIR TER ALGUMAS INFORMAÇOES DELAS
    EXEMPLO

    COORDENADAS DO CENTRO DELA
    RAIO DA ESFERA
    DIAMETRO DA ESFERA 
    TALVEZ A COR

*/

/// @brief Se front_face for 1 significa que o raio bateu na parte de tras da esfera.
///        Se front_face for 0 significa que batemos de frente na esfera
/// @param ray 
/// @param  
/// @param record 
static void set_face_normal(const t_ray *ray,const double outward_normal[3],t_hit_record *record)
{
    

    record->front_face = vec3_dot(ray->direction, outward_normal) < 0;

   // Se o raio vem do lado oposto à normal, mantemos a normal como está
    // Caso contrário, invertemos a direção da normal
    if (record->front_face)
        vec3_copy(record->normal, outward_normal);
    else
        vec3_negate(record->normal,outward_normal);
}

static bool    have_hit_sphere(const t_sphere *sphere,const t_ray *ray,t_interval t_ray,t_hit_record *record)
{
	double	oc[3];
	double	discriminant;
    double  sqrtd;
    vec3_sub(oc, ray->origin, sphere->cords);            // oc = center - r->origin
    double a = vec3_dot(ray->direction, ray->direction);
    double h = vec3_dot(ray->direction, oc); 
    double c = vec3_dot(oc, oc) - sphere->radius * sphere->radius;

    discriminant = h * h - a * c;
    if(0 > discriminant)
        return false;
    //Temos algum intersecao
    sqrtd = sqrt(discriminant);
    double root;

    root = (-h - sqrtd) / a;
    if(!interval_surrounds(root,t_ray))
    {
        root = (-h + sqrtd) / a;
        if(!interval_surrounds(root,t_ray))
            return false;
    }

    record->t = root;
    ray_at(record->t,*ray,record->position);
    double outward_normal[3];



    vec3_sub(outward_normal, record->position, sphere->cords);
    vec3_normalize(outward_normal, outward_normal);
    set_face_normal(ray,outward_normal,record);
    return true;
} 



 bool hit_spheres(t_control_panel *scene, const t_ray *ray, t_interval t_ray, t_hit_record *record)
{
    bool hit_anything = false;
    double closest_so_far = t_ray.max;
    t_hit_record temp_rec;

    size_t i = 0;
    while (i < scene->data.sphere_count) {
        if (have_hit_sphere(&scene->sphere[i], ray, interval_create(t_ray.min,closest_so_far), &temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            *record = temp_rec;  // Copia o registro do hit mais próximo
        }
        i++;
    }

    return hit_anything;
} 


bool hit_world(t_control_panel *scene, const t_ray *ray,  t_interval t_ray, t_hit_record *record)
{
    t_hit_record temp_rec;
    bool hit_anything = false;
    double closest_so_far = t_ray.max;
    
    // Verificamos colisões com todas as esferas
    if (hit_spheres(scene, ray,interval_create(t_ray.min,closest_so_far), &temp_rec)) {
        hit_anything = true;
        closest_so_far = temp_rec.t;
        *record = temp_rec;
    }

    //EM BREVE VAMOS TER OUTRAS FUNCOES DE HIT YUPIII    
    return hit_anything;
}


void random_on_hemisphere(double normal[3],double out[3])
{
    double on_unit_sphere[3];

    
    vec3_zero(on_unit_sphere);
    vec3_random_utit_vector(on_unit_sphere);
    if(vec3_dot(on_unit_sphere,normal) > 0.0)
    {
        vec3_copy(out,on_unit_sphere);
    }else
    {
        vec3_negate(out,on_unit_sphere);
    }

}