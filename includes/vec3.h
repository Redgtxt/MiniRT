#ifndef VEC3_H
# define VEC3_H

/*Vectos Utils*/
double vec3_lenght(const double vector[3]);
void vec3_set(double v[3], double x, double y, double z);
void vec3_copy(double dest[3], const double src[3]);
void vec3_scale(double out[3], const double v[3], double s);
void vec3_add(double out[3], const double a[3], const double b[3]);
void vec3_sub(double out[3], const double a[3], const double b[3]);
void vec3_multiply(double out[3], const double a[3], const double b[3]);
void vec3_divide(double out[3], const double v[3], double t);
double vec3_dot(const double a[3], const double b[3]);
void vec3_negate(double out[3], const double v[3]);
void vec3_zero(double v[3]);
void vec3_unit_vector(double out[3], const double v[3]);
void vec3_sub_chain(double out[3], const double a[3], const double b[3],
                    const double c[3]);
void vec3_random(double out[3]);
void vec3_random_range(double out[3],double min,double max);
void vec3_random_utit_vector(double good_point[3]);
bool vec3_near_zero(double out[3]);
void vec3_cross(double out[3], const double a[3], const double b[3]);
double vec3_length(const double v[3]);
void vec3_add_scaled(const double base[3], const double direction[3], double scalar, double result[3]);
#endif
