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

static bool    have_hit_sphere(const t_sphere *sphere,const t_ray *ray,double ray_tmin,double ray_tmax,t_hit_record *record)
{
	double	oc[3];
	double	discriminant;
    double  sqrtd;
    vec3_sub(oc, sphere->cords, ray->origin);               // oc = center - r->origin
	double a = vec3_lenght(ray->direction);          // direction.length_squared()
	double h = vec3_dot(ray->direction, oc);         // dot(direction, oc)
	double c = vec3_lenght(oc) - sphere->radius * sphere->radius;  // oc.length_squared()- radius²

    discriminant = h * h - a * c;
    if(0 > discriminant)
        return false;
    
    //Temos algum intersecao
    sqrtd = sqrt(discriminant);
    double root;

    root = (h - sqrtd) / a;
    if(root <= ray_tmin || ray_tmax <= root)
    {
        root = (h + sqrtd) / a;
        if(root <= ray_tmin || ray_tmax <= root)
            return false;
    }

    record->t = root;
    ray_at(record->t,*ray,record->position);
    double temp[3];
    vec3_sub(temp,record->position ,sphere->cords);
    vec3_divide(record->normal,temp,sphere->radius);
    return true;
    
} 
 bool hit_spheres(t_control_panel *scene, const t_ray *ray, double ray_tmin, 
                 double ray_tmax, t_hit_record *record)
{
    bool hit_anything = false;
    double closest_so_far = ray_tmax;
    t_hit_record temp_rec;

    size_t i = 0;
    while (i < scene->data.sphere_count) {
        if (have_hit_sphere(&scene->sphere[i], ray, ray_tmin, closest_so_far, &temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            *record = temp_rec;  // Copia o registro do hit mais próximo
        }
        i++;
    }

    return hit_anything;
} 


