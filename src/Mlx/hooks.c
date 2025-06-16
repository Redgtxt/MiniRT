#include "../../includes/miniRT.h"

/**
 * Coloca um pixel na imagem em uma posição específica
 * @param data Estrutura contendo informações MLX
 * @param x Coordenada X do pixel
 * @param y Coordenada Y do pixel
 * @param color Cor em formato RGB (0xRRGGBB)
 */
void my_mlx_pixel_put(t_control_panel *control_panel, int x, int y, int color)
{
    char *dst;
    t_mlx *mlx_data;

    mlx_data = control_panel->mlx;
    if (x >= 0 && x < control_panel->camera.image_width && y >= 0 && y < control_panel->camera.image_height)
    {
        dst = mlx_data->addr + (y * mlx_data->line_length + x * (mlx_data->bits_per_pixel / 8));
        *(unsigned int *)dst = color;
    }
}

int close_window(t_control_panel *control_panel)
{
    t_mlx *mlx_data;

    mlx_data = control_panel->mlx;
    if (mlx_data->img)
        mlx_destroy_image(mlx_data->mlx, mlx_data->img);
    if (mlx_data->win)
        mlx_destroy_window(mlx_data->mlx, mlx_data->win);
    if (mlx_data->mlx)
    {
        mlx_destroy_display(mlx_data->mlx);
        free(mlx_data->mlx);
    }
    free_control_panel_lists(control_panel);
    exit(0);
    return (0);
}
static void clear_image(t_control_panel *control_panel)
{
    t_mlx *mlx_data;

    mlx_data = control_panel->mlx;
    ft_bzero(mlx_data->addr, control_panel->camera.image_height * mlx_data->line_length);

    mlx_put_image_to_window(mlx_data->mlx, mlx_data->win, mlx_data->img, 0, 0);
}
static void config_antialising_render(int keycode, t_control_panel *control_panel)
{
    if (keycode == '1')
    {
        control_panel->camera.antialiasing = true;
        setup_antialiasing(control_panel, 16);
        printf("\n" HMAG "FAST Antialiasing: APPLYING with 16 samples" reset "\n");
        clear_image(control_panel);
        render_scene(control_panel);
    }
    else if (keycode == '2')
    {
        control_panel->camera.antialiasing = true;
        setup_antialiasing(control_panel, 50);
        printf("\n" HMAG "MEDIUM Antialiasing: APPLYING with 50 samples" reset "\n");
        clear_image(control_panel);
        render_scene(control_panel);
    }
    else if (keycode == '3')
    {
        control_panel->camera.antialiasing = true;
        setup_antialiasing(control_panel, 100);
        printf("\n" HMAG "SLOW Antialiasing: APPLYING with 100 samples" reset "\n");
        clear_image(control_panel);
        render_scene(control_panel);
    }
    else if (keycode == 48)
    {
        control_panel->camera.antialiasing = false;
        setup_antialiasing(control_panel, 1);
        printf("\n" HMAG "Antialiasing: DISABLED" reset "\n");
        clear_image(control_panel);
        render_scene(control_panel);
    }
}
static void change_object_brightness(int keycode, t_control_panel *control_panel)
{
    t_interval interval;

    interval = interval_create(0, 1);
    if (keycode == ARROW_LEFT_KEY)
    {
        control_panel->light.object_brightness -= .1;
        control_panel->light.object_brightness = clamp(control_panel->light.object_brightness, interval);
        printf(HMAG "Object brightness: %.1f " reset, control_panel->light.object_brightness);

        clear_image(control_panel);
        render_scene(control_panel);
    }
    if (keycode == ARROW_RIGHT_KEY)
    {

        control_panel->light.object_brightness += .1;
        control_panel->light.object_brightness = clamp(control_panel->light.object_brightness, interval);
        printf(HMAG "Object brightness: %.1f " reset, control_panel->light.object_brightness);

        clear_image(control_panel);
        render_scene(control_panel);
    }
}
int key_hook(int keycode, t_control_panel *control_panel)
{
    printf("Tecla pressionada: %d (%c)\n", keycode, keycode);
    if (keycode == KEY_ESC)
    {
        close_window(control_panel);
    }
    config_antialising_render(keycode, control_panel);
    if (keycode == 'r')
    {
        control_panel->camera.antialiasing = false;
        setup_antialiasing(control_panel, 1);
        ft_printf(BHYEL "\rResetting scene" reset "\n");
        clear_image(control_panel);
        render_scene(control_panel);
    }
    change_object_brightness(keycode, control_panel);
    return (0);
}

void game_hooks(t_control_panel *control_panel)
{
    t_mlx *mlx_data;

    mlx_data = control_panel->mlx;
    mlx_hook(mlx_data->win, 17, 0, close_window, control_panel);
    mlx_key_hook(mlx_data->win, key_hook, control_panel);
}
