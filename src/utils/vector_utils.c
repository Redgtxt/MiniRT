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
                    const double c[3], const double d[3])
{
    out[0] = a[0] - b[0] - c[0] - d[0];
    out[1] = a[1] - b[1] - c[1] - d[1];
    out[2] = a[2] - b[2] - c[2] - d[2];
}

/// @brief Criar um vetor zero (0,0,0)
/// @param v vetor que vai ser definido como zero
void vec3_zero(double v[3])
{
    v[0] = 0.0;
    v[1] = 0.0;
    v[2] = 0.0;
}