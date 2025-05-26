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
            mlx_pixel_put(mlx, mlx_win, i,j, 0x0000FF); 
            mlx_pixel_put(mlx, mlx_win, i,0, 0xFF0000); 
           j++;
        }
        
        i++;
    }
    
   
    ft_printf("Window created successfully\n");
    ft_printf("WOW AMAZING VIEW\n");
    ft_printf("WOW AMAZING BANANA\n");

    mlx_loop(mlx);
    
    return (0);
}