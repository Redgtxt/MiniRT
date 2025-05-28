#include "../../includes/miniRT.h"


//returna o tamanho de um vetor ao quadrado
/*
    esta funcao serve para calcular o valor total de um vetor para depois so ter de calcular a raiz quadrada em um valor em ves de ter de fazer em varios individuais
*/
static double lenght_squared(double vector[3])
{
    return (vector[0] * vector[0] + vector[1] * vector[1] + vector[2] * vector[2]);
}

//vai returnar o tamanho de um vetor 
double lenght_vec(double vector[3])
{
    return (sqrt(lenght_squared(vector)));
}

