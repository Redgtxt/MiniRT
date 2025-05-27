#include "../includes/miniRT.h"

//Ray_Maker
/*
    vou tentar criar um raio
*/

/// @brief Will store the values of the ray
/// @param cords 
/// @param vector3 
/// @return 0 in sucess
int create_ray(t_ray *ray)
{
    ray->cords[0] = 0;
    ray->cords[1] = 0;
    ray->cords[2] = 0;

    ray->vec3[0] = 0;
    ray->vec3[1] = 1;
    ray->vec3[2] = 0;

    return 0;
}
/*

double get_t(t_ray ray, double t)
{
    t_ray result;
    return(ray.cords + t * ray.vec3);
}
*/

int main(void)
{
    void *mlx;
    void *mlx_win;


    t_ray ray;  // alocação no stack

    create_ray(&ray);

    printf("%f\n", ray.vec3[1]);

    ft_printf("MiniRT Starting...\n");

    mlx = mlx_init();
    if (!mlx)
    {
        ft_printf("Error: Could not initialize MLX\n");
        return (1);
    }

    mlx_win = mlx_new_window(mlx, WINDOW_HEIGHT, WINDOW_WIDTH, "miniRT");
    if (!mlx_win)
    {
        ft_printf("Error: Could not create window\n");
        return (1);
    }

    int i = 0;
    while (WINDOW_HEIGHT >= i)
    {

        int j = 0;

        while (WINDOW_WIDTH >= j)
        {
            mlx_pixel_put(mlx, mlx_win, i, j, 0x0000FF);
            mlx_pixel_put(mlx, mlx_win, i, 0, 0xFF0000);
            j++;
        }

        i++;
    }

    ft_printf("Render Completed\n");
    mlx_loop(mlx);

    return (0);
}