#include "../../includes/miniRT.h"

/**
 * Coloca um pixel na imagem em uma posição específica
 * @param data Estrutura contendo informações MLX
 * @param x Coordenada X do pixel
 * @param y Coordenada Y do pixel
 * @param color Cor em formato RGB (0xRRGGBB)
 */
void    my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
    char    *dst;
    
    if (x >= 0 && x < data->width && y >= 0 && y < data->height)
    {
        dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
        *(unsigned int*)dst = color;
    }
}

int	close_window(t_mlx *mlx_data)
{
	mlx_destroy_image(mlx_data->mlx, mlx_data->img);
    mlx_destroy_window(mlx_data->mlx, mlx_data->win);
    mlx_destroy_display(mlx_data->mlx);
    free(mlx_data->mlx);
	mlx_loop_end(mlx_data->mlx);
    return (0);
}

int	key_hook(int keycode, t_mlx *mlx_data)
{
	if (keycode == KEY_ESC)
		close_window(mlx_data);
	return (0);
}

void	game_hooks(t_mlx *mlx_data)
{
	mlx_hook(mlx_data->win, 17, 0, close_window, mlx_data);
	mlx_key_hook(mlx_data->win, key_hook, mlx_data);
}