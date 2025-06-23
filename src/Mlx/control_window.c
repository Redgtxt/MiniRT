#include "../../includes/miniRT.h"

#define W_WIDTH 400
#define W_HEIGHT 400

int create_control_window(t_control_panel *cp)
{
    t_win_config *control_data;
    t_button my_button = {100, 100, 200, 50, 0x00FF00};

    // Alocar memória para a estrutura de controle
    control_data = malloc(sizeof(t_win_config));
    if (!control_data)
        return (1);

    control_data->mlx = cp->mlx->mlx;
    if (!control_data->mlx)
    {
        ft_printf("Error: Could not initialize MLX\n");
        free(control_data);
        return (1);
    }

    control_data->win = mlx_new_window(control_data->mlx, W_WIDTH, W_HEIGHT, "miniRT Control");
    if (!control_data->win)
    {
        ft_printf("Error: Could not create window\n");
        free(control_data);
        return (1);
    }

    control_data->img = mlx_new_image(control_data->mlx, W_WIDTH, W_HEIGHT);
    control_data->addr = mlx_get_data_addr(control_data->img, &control_data->bits_per_pixel,
                                           &control_data->line_length, &control_data->endian);

    // Armazenar os dados da janela de controle
    cp->config_win = control_data;

    // Configurar o botão com as dimensões corretas
    control_data->button = my_button;

    draw_button(cp, my_button);
    mlx_put_image_to_window(control_data->mlx, control_data->win, control_data->img, 0, 0);

    mlx_mouse_hook(control_data->win,mouse_handler,cp);
    return (0);
}

static void pixel_put_win_control(t_control_panel *cp, int x, int y, int color)
{
    char *dst;
    t_win_config *control_data;
    t_interval x_interval;
    t_interval y_interval;

    control_data = cp->config_win;
    if (!control_data)
        return;

    // Criar intervalos para os limites da janela de controle
    x_interval = interval_create(0, W_WIDTH - 1);
    y_interval = interval_create(0, W_HEIGHT - 1);

    // Verificar se o pixel está dentro dos limites
    if (interval_contains(x, x_interval) && interval_contains(y, y_interval))
    {
        dst = control_data->addr + (y * control_data->line_length + x * (control_data->bits_per_pixel / 8));
        *(unsigned int *)dst = color;
    }
}

void draw_button(t_control_panel *cp, t_button button)
{
    int i;
    int j;

    i = 0;
    while (i < button.height)
    {
        j = 0;
        while (j < button.width)
        {
            pixel_put_win_control(cp, button.x + j, button.y + i, button.color);
            j++;
        }
        i++;
    }
}

int mouse_handler(int mousecode, int x, int y, void *param)
{
    t_control_panel *cp = (t_control_panel *)param;
    t_button button;
    t_interval x_interval;
    t_interval y_interval;
    
    if (!cp || !cp->config_win)
        return (0);
        
    button = cp->config_win->button;
    
    if (mousecode == 1)
    {
        x_interval = interval_create(button.x, button.x + button.width);
        y_interval = interval_create(button.y, button.y + button.height);
        if (interval_contains(x, x_interval) && interval_contains(y, y_interval))
        {
            printf("Botão clicado!\n");
            render_scene(cp);
        }
    }
    return (0);
}
