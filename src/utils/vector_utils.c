#include "../../includes/miniRT.h"

//returna o tamanho de um vetor ao quadrado
/*
    esta funcao serve para calcular o valor total de um vetor para depois so ter de calcular a raiz quadrada em um valor em ves de ter de fazer em varios individuais
*/
static double lenght_squared(const double vector[3])
{
    return (vector[0] * vector[0] + vector[1] * vector[1] + vector[2] * vector[2]);
}

//vai returnar o tamanho de um vetor
double vec3_lenght(const double vector[3])
{
    return (sqrt(lenght_squared(vector)));
}


void	vec3_normalize(double out[3], const double v[3])
{
	double	temp_v[3];
	double	len;

	vec3_copy(temp_v, v);
	len = vec3_lenght(temp_v);
	if (len == 0.0)
		vec3_zero(out); // evitar divisão por zero
	else
		vec3_scale(out, v, 1.0 / len);
}

/// @brief Calcular um ponto ao longo de um raio
/// @param t parâmetro do raio (distância)
/// @param ray raio que contém origem e direção
/// @param result vetor onde será armazenado o ponto calculado
///
/// Fórmula: P(t) = A + t*B
/// onde A é a origem do raio e B é a direção do raio
void ray_at(double t, t_ray ray, double result[3])
{
    double scaled_direction[3];

    // Escalar a direção pelo parâmetro t
    vec3_scale(scaled_direction, ray.direction, t);

    // Somar a origem com a direção escalada
    vec3_add(result, ray.origin, scaled_direction);
}

/// @brief Change the value of a VECTOR
/// @param v vector that you want to change the value
/// @param x x position
/// @param y y position
/// @param z z position
void vec3_set(double v[3], double x, double y, double z)
{
	v[0] = x;
	v[1] = y;
	v[2] = z;
}
/// @brief Copy the content of a VECTOR to other VECTOR
/// @param dest Vector returned from copied
/// @param src  Vector used to copy
void vec3_copy(double dest[3], const double src[3])
{
	dest[0] = src[0];
	dest[1] = src[1];
	dest[2] = src[2];
}

			/*	ARITHETIC OPERATIONS	*/


/// @brief Add the value of a complet vector example a[0] + b[0]
/// @param out // Vector with the final result
/// @param a //Vector used to calculat
/// @param b //Vector used to calculat
void vec3_add(double out[3], const double a[3], const double b[3])
{
	out[0] = a[0] + b[0];
	out[1] = a[1] + b[1];
	out[2] = a[2] + b[2];
}

/// @brief Subtract the value of a complet vector example a[0] - b[0]
/// @param out // Vector with the final result
/// @param a //Vector used to calculat
/// @param b //Vector used to calculat
void vec3_sub(double out[3], const double a[3], const double b[3])
{
	out[0] = a[0] - b[0];
	out[1] = a[1] - b[1];
	out[2] = a[2] - b[2];
}

/// @brief Element-wise multiplication of two vectors
/// @param out output vector to store the result
/// @param a first input vector
/// @param b second input vector
void vec3_multiply(double out[3], const double a[3], const double b[3])
{
    out[0] = a[0] * b[0];
    out[1] = a[1] * b[1];
    out[2] = a[2] * b[2];
}

/// @brief Divide a vector by a scalar
/// @param out output vector to store the result
/// @param v input vector
/// @param t scalar divisor
void vec3_divide(double out[3], const double v[3], double t)
{
    vec3_scale(out, v, 1.0 / t);
}


/// @brief Scale a VECTOR by a scalar value
/// @param out vector to store the result
/// @param v input vector
/// @param s scalar value
void vec3_scale(double out[3], const double v[3], double scaleFactor)
{
	out[0] = v[0] * scaleFactor;
	out[1] = v[1] * scaleFactor;
	out[2] = v[2] * scaleFactor;
}


/// @brief Calculate the dot product of two vectors
/// @param a First input vector
/// @param b Second input vector
/// @return The dot product of the two vectors
double vec3_dot(const double a[3], const double b[3])
{
	return (a[0]*b[0] + a[1]*b[1] + a[2]*b[2]);
}


/// @brief Negate a vector (equivalent to operator-)
/// @param out output vector to store the result
/// @param v input vector
void vec3_negate(double out[3], const double v[3])
{
    out[0] = -v[0];
    out[1] = -v[1];
    out[2] = -v[2];
}

/// @brief Criar um vetor unitário (normalizado) a partir de um vetor
/// @param out vetor de saída onde será armazenado o vetor unitário
/// @param v vetor de entrada a ser normalizado
///
/// Esta função calcula v / |v| onde |v| é o comprimento do vetor
void vec3_unit_vector(double out[3], const double v[3])
{
    double len = vec3_lenght((double*)v);

    if (len == 0.0)
        vec3_zero(out);  // evitar divisão por zero
    else
        vec3_scale(out, v, 1.0 / len);
}

void vec3_sub_chain(double out[3], const double a[3], const double b[3],
                    const double c[3])
{
    out[0] = a[0] - b[0] - c[0];
    out[1] = a[1] - b[1] - c[1];
    out[2] = a[2] - b[2] - c[2];
}

/// @brief Criar um vetor zero (0,0,0)
/// @param v vetor que vai ser definido como zero
void vec3_zero(double v[3])
{
    v[0] = 0.0;
    v[1] = 0.0;
    v[2] = 0.0;
}

/**
 * @brief Gera um vetor com valores aleatórios no intervalo [0,1)
 * @param out Vetor de saída para armazenar os valores gerados
 */
void vec3_random(double out[3])
{
    out[0] = random_double_0_to_1();
    out[1] = random_double_0_to_1();
    out[2] = random_double_0_to_1();
}

/**
 * @brief Gera um vetor com valores aleatórios no intervalo [min,max)
 * @param out Vetor de saída para armazenar os valores gerados
 * @param min Valor mínimo do intervalo
 * @param max Valor máximo do intervalo
 */
void vec3_random_range(double out[3],double min,double max)
{
    out[0] = random_double(min,max);
    out[1] = random_double(min,max);
    out[2] = random_double(min,max);
}

void vec3_random_utit_vector(double good_point[3])
{
    double p[3]; //position of the point created
    double  lensq;
    vec3_zero(p);
    vec3_zero(good_point);
    while (true)
    {
        vec3_random_range(p,-1,1);
        lensq = lenght_squared(p);
        if(1e-160 < lensq && lensq <= 1)//1 × 10^(-160)
        {
            vec3_divide(good_point,p,sqrt(lensq));
            break;
        }
    }
}

bool vec3_near_zero(double out[3])
{
    double s = 1e-8;
    return fabs(out[0]) < s && fabs(out[1]) < s && fabs(out[2]) < s;
}

void vec3_add_dir(vec3 original[3], vec3 dir[3], double dist)
{
    original[0] = original[0] + dir[0] * dist;
    original[1] = original[1] + dir[1] * dist;
    original[2] = original[2] + dir[2] * dist;
}
/// @brief Calcular o produto vetorial (cross product) de dois vetores
/// @param out vetor de saída para armazenar o resultado
/// @param a primeiro vetor
/// @param b segundo vetor
void vec3_cross(double out[3], const double a[3], const double b[3])
{
    out[0] = a[1] * b[2] - a[2] * b[1];
    out[1] = a[2] * b[0] - a[0] * b[2];
    out[2] = a[0] * b[1] - a[1] * b[0];
}

double vec3_length(const double v[3])
{
    return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
}

void	vec3_add_scaled(double out[3], const double a[3], const double b[3],
		double s)
{
	double	scaled_b[3];

	vec3_scale(scaled_b, b, s);
	vec3_add(out, a, scaled_b);
}
/// @brief Reflect a vector v around a normal n
/// @param v vector to be reflected
/// @param n normal vector to reflect around
/// @param out output vector to store the reflected result
/// @details The reflection formula is: reflected = v - 2 * dot(v, n) * n
/// where dot(v, n) is the dot product of v and n.
/// This function assumes that n is a unit normal vector.
/// If n is not unit length, the result will not be correct.
/// @note This function modifies the out vector directly.
void reflect(const double v[3], const double n[3], double out[3])
{
    double dot_product = vec3_dot(v, n);
    double scaled_normal[3];
    
    vec3_scale(scaled_normal, n, 2.0 * dot_product);
    vec3_sub(out, v, scaled_normal);
}

/// @brief Refract a vector through a surface with given refractive indices ratio
/// @param uv incident vector (should be normalized)
/// @param n surface normal (should be normalized)
/// @param etai_over_etat ratio of refractive indices (eta_incident / eta_transmitted)
/// @param out output vector to store the refracted ray
void refract(const double uv[3], const double n[3], double etai_over_etat, double out[3])
{
    double uv_negated[3];
    double cos_theta;
    double r_out_perp[3];
    double r_out_parallel[3];
    double cos_theta_n[3];
    double temp[3];
    double perp_length_sq;
    double parallel_magnitude;

    // Calculate -uv
    vec3_negate(uv_negated, uv);
    
    // cos_theta = fmin(dot(-uv, n), 1.0)
    cos_theta = vec3_dot(uv_negated, n);
    if (cos_theta > 1.0)
        cos_theta = 1.0;
    
    // r_out_perp = etai_over_etat * (uv + cos_theta*n)
    vec3_scale(cos_theta_n, n, cos_theta);
    vec3_add(temp, uv, cos_theta_n);
    vec3_scale(r_out_perp, temp, etai_over_etat);
    
    // r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n
    perp_length_sq = lenght_squared(r_out_perp);
    parallel_magnitude = sqrt(fabs(1.0 - perp_length_sq));
    vec3_scale(r_out_parallel, n, -parallel_magnitude);
    
    // return r_out_perp + r_out_parallel
    vec3_add(out, r_out_perp, r_out_parallel);
}

/// @brief Schlick's approximation for reflectance (Fresnel effect)
/// @param cosine cosine of the incident angle
/// @param refraction_index refractive index of the material
/// @return reflectance probability (0.0 to 1.0)
double schlick_reflectance(double cosine, double refraction_index)
{
    double r0 = (1.0 - refraction_index) / (1.0 + refraction_index);
    r0 = r0 * r0;
    return r0 + (1.0 - r0) * pow((1.0 - cosine), 5);
}

/// @brief Se front_face for 1 significa que o raio bateu na parte de tras da esfera.
///        Se front_face for 0 significa que batemos de frente na esfera
/// @param ray
/// @param
/// @param record
void	set_face_normal(const t_ray *ray, const double outward_normal[3],
			t_hit_record *record)
{
    record->front_face = vec3_dot(ray->direction, outward_normal) < 0;
    if (record->front_face)
        vec3_copy(record->normal, outward_normal);
    else
        vec3_negate(record->normal, outward_normal);
}