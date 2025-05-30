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
/// @brief Criar um vetor zero (0,0,0)
/// @param v vetor que vai ser definido como zero
void vec3_zero(double v[3])
{
    v[0] = 0.0;
    v[1] = 0.0;
    v[2] = 0.0;
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