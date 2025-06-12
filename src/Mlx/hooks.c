#include "../../includes/miniRT.h"

/**
 * Coloca um pixel na imagem em uma posição específica
 * @param data Estrutura contendo informações MLX
 * @param x Coordenada X do pixel
 * @param y Coordenada Y do pixel
 * @param color Cor em formato RGB (0xRRGGBB)
 */
void    my_mlx_pixel_put(t_control_panel *control_panel, t_mlx *data, int x, int y, int color)
{
    char    *dst;
    if (x >= 0 && x < control_panel->camera.image_width && y >= 0 && y < control_panel->camera.image_height)
    {
        dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
        *(unsigned int*)dst = color;
    }
}

int	close_window(t_mlx *mlx_data)
{
    if (mlx_data->img)
        mlx_destroy_image(mlx_data->mlx, mlx_data->img);
    if (mlx_data->win)
        mlx_destroy_window(mlx_data->mlx, mlx_data->win);
    if (mlx_data->mlx)
    {
        mlx_destroy_display(mlx_data->mlx);
        free(mlx_data->mlx);
    }
    exit(0);
    return (0);
}
static void clear_image(t_control_panel *control_panel)
{
    t_mlx *mlx_data;
    
    mlx_data = control_panel->mlx;
    ft_bzero(mlx_data->addr,control_panel->camera.image_height * mlx_data->line_length);
    
    mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, mlx_data->img, 0, 0);
}

int	key_hook(int keycode, t_control_panel *control_panel)
{
	if (keycode == KEY_ESC)
    {
		close_window(control_panel->mlx);
    }else if(keycode == '1')
    {
         control_panel->camera.antialiasing = true;
        setup_antialiasing(control_panel, 16);
        clear_image(control_panel);
        render_scene(control_panel);
    }else if(keycode == '2')
    {
         control_panel->camera.antialiasing = true;
        setup_antialiasing(control_panel, 50);
        clear_image(control_panel);
        render_scene(control_panel);
    }else if(keycode == '3')
    {
         control_panel->camera.antialiasing = true;
        setup_antialiasing(control_panel, 100);
        clear_image(control_panel);
        render_scene(control_panel);
    }else if(keycode == 'R')
    {
        
        control_panel->camera.antialiasing = false;
        clear_image(control_panel);
        render_scene(control_panel);
    }
    
	return (0);
}

void	game_hooks(t_mlx *mlx_data)
{
	mlx_hook(mlx_data->win, 17, 0, close_window, mlx_data);
	mlx_key_hook(mlx_data->win, key_hook, mlx_data);
}
