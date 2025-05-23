#include "../includes/miniRT.h"

int main(void)
{
    void *mlx;
    void *mlx_win;
    
    ft_printf("MiniRT Starting...\n");
    
    mlx = mlx_init();
    if (!mlx)
    {
        ft_printf("Error: Could not initialize MLX\n");
        return (1);
    }
    
    mlx_win = mlx_new_window(mlx, 800, 600, "miniRT");
    if (!mlx_win)
    {
        ft_printf("Error: Could not create window\n");
        return (1);
    }
    
    ft_printf("Window created successfully\n");
    ft_printf("WOW AMAZING VIEW\n");

    mlx_loop(mlx);
    
    return (0);
}