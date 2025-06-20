/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:40:49 by randrade          #+#    #+#             */
/*   Updated: 2025/06/20 17:50:32 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H
#include "../Library/ft_printf/ft_printf.h"
#include "../Library/get_next_line/get_next_line.h"
#include "../Library/libft/libft.h"
#include "../Library/minilibx-linux/mlx.h"
#include "miniRT_error_p.h"
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <float.h>
#include <unistd.h>
#include <time.h> //BONUS
#include "vec3.h"
#include "interval.h"

//	Printf colors
#define REDHB "\e[0;101m"
#define GRNHB "\e[0;102m"
#define reset "\e[0m"
#define BBLK "\e[1;30m"
#define BHGRN "\e[1;92m"
#define BHYEL "\e[1;93m"
#define HMAG "\e[1;95m"
// Cores para a interface
#define COLOR_WHITE     0xFFFFFF
#define COLOR_BLACK     0x000000
#define COLOR_GRAY      0x808080
#define COLOR_DARK_GRAY 0x404040
#define COLOR_BLUE      0x0080FF
#define COLOR_RED       0xFF0000


#define PI 3.1415926535897932385
#define D_INFINITY ((double)INFINITY)
#define WINDOW_HEIGHT 360
#define WINDOW_WIDTH 1280
#define KEY_ESC 65307
#define ARROW_UP_KEY 65362
#define ARROW_DOWN_KEY 65364
#define ARROW_LEFT_KEY 65361
#define ARROW_RIGHT_KEY 65363

typedef unsigned char mini_int;
typedef double vec3;

#define TRANS 0
#define RED 1
#define GREEN 2
#define BLUE 3

typedef enum e_material_type
{
	LAMBERTIAN,
	METAL
}			t_material_type;

typedef struct s_ray
{
	vec3 origin[3];

	double direction[3];

} t_ray;

typedef struct s_material
{
	t_material_type type;
	double			albedo[3];
}			t_material;

typedef struct s_data_scatter
{
	t_ray	scattered;
    double	attenuation[3];
}				t_data_scatter;

typedef struct s_hit_record
{
	double position[3];
	double normal[3];
	double t;
	bool front_face;
	t_material *material;
} t_hit_record;

// Estrutura para o slider
typedef struct s_slider
{
    int x;          // posição x do slider
    int y;          // posição y do slider
    int width;      // largura do slider
    int height;     // altura do slider
    double min_val; // valor mínimo
    double max_val; // valor máximo
    double *value;  // ponteiro para o valor atual
    int dragging;   // flag se está sendo arrastado
    char *label;    // texto do slider
} t_slider;

// Estrutura para a janela de controle
typedef struct s_control_window
{
    void *mlx;
    void *win;
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
    int width;
    int height;
    t_slider *sliders;
    int slider_count;
} t_control_window;

typedef struct s_mlx
{
	void *mlx;
	void *win;
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
	t_control_window *control_win;//Window 
} t_mlx;

typedef struct s_data
{
	size_t amb_light_count;
	size_t camera_count;
	size_t light_count;
	size_t sphere_count;
	size_t plane_count;
	size_t cylinder_count;
} t_data;

typedef struct s_amb_light
{
	double light_force;
	double rgb[3];
} t_amb_light;

typedef struct s_camera
{
	vec3 cords[3];

	vec3 vec3[3];

	mini_int fov;

	int image_height; // Rendered image height
	int image_width;
	double aspect_ratio;
	double pixel00_loc[3];	 // Location of pixel 0, 0
	double pixel_delta_u[3]; // Offset to pixel to the right
	double pixel_delta_v[3]; // Offset to pixel below
	int samples_per_pixel;	 // Count of random samples for each pixel
	double pixel_samples_scale;

	double	lookat[3];
	double	vup[3];	

	double	u[3];
	double	v[3];
	double	W[3];

	double	max_bounces;// Maximum number of ray bounces into scene

	bool antialiasing;
} t_camera;

typedef struct s_light
{
	vec3 cords[3];
	float brightness;
	double	object_brightness;
	double rgb[3];
} t_light;

typedef struct s_sphere
{
	// coordenadas do centro da esfera

	vec3 cords[3];

	/*Diametro da Espera
	(E passado no subject)
	*/
	double d;
	// Acho que e fixe ter para calculos (vamos ter de o calcular)
	double radius;
	double rgb[3];
	t_material	material;
	struct s_sphere *prev;
	struct s_sphere *next;
} t_sphere;

typedef struct s_plane
{
	//    PODE NAO SER O CENTRO (PELOS VISTOS PLANOS SAO INFINITOS)

	vec3 cords[3];

	vec3 vec3[3];

	double rgb[3];
	t_material	material;
	struct s_plane *prev;
	struct s_plane *next;
} t_plane;

typedef struct s_cylinder
{
	//     coordenadas do centro do CILINDRO

	vec3 cords[3];
	vec3 vec3[3];

	/*
	Diametro do CILINDRO(E passado no subject)
	*/
	double d;
	// Acho que e fixe ter para calculos (vamos ter de o calcular)
	double radius;
	double height;
	double rgb[3];
	t_material	material;
	struct s_cylinder *prev;
	struct s_cylinder *next;
} t_cylinder;

typedef struct s_control_panel
{
	t_amb_light amb_light;
	t_camera camera;
	t_light light;
	t_sphere *sphere;
	t_plane *plane;
	t_cylinder *cylinder;
	t_data data;
	t_error_log error_log;
	t_mlx	*mlx;
} t_control_panel;

// MLX
void    my_mlx_pixel_put(t_control_panel *control_panel, int x, int y, int color);
int close_window(t_control_panel *control_panel);
int	key_hook(int keycode, t_control_panel *control_panel);
void game_hooks(t_control_panel *control_panel);
void clear_image(t_control_panel *control_panel);
void config_antialising_render(int keycode, t_control_panel *control_panel);
void change_object_brightness(int keycode, t_control_panel *control_panel);
void change_amb_light_brightness(int keycode, t_control_panel *control_panel);

//Window control
void control_mlx_pixel_put(t_control_window *control_win, int x, int y, int color);

/*Ray functions*/
void init_ray(t_ray *ray);
void create_ray(t_ray *ray, const double origin[3], const double direction[3]);
void ray_origin(const t_ray *ray, double out[3]);
void ray_direction(const t_ray *ray, double out[3]);
void ray_at(double t, t_ray ray, double result[3]);
void ray_color(t_control_panel *control_panel,int depth, const t_ray *ray, double out_color[3]);
void vec3_normalize(double out[3], const double v[3]);
t_ray get_ray(int i, int j, t_control_panel *control_panel);

/*UITLS*/
double degrees_to_radians(double degrees);
double random_double_0_to_1();
double random_double(double min, double max);
int write_color(double r, double g, double b);
/*	sphere	*/

/*	Init	Sphere array	*/
bool linked_list_to_sphere_array(t_sphere **sphere_list, int size_array);
bool linked_list_to_plane_array(t_plane **plane_list, int size_array);

/*Sphere Collision*/
bool hit_spheres(t_control_panel *scene, const t_ray *ray, t_interval t_ray, t_hit_record *record);
bool hit_world(t_control_panel *scene, const t_ray *ray, t_interval t_ray, t_hit_record *record);
void random_on_hemisphere(double normal[3],double out[3]);
void set_face_normal(const t_ray *ray,const double outward_normal[3],t_hit_record *record);
 bool hit_planes(t_control_panel *scene, const t_ray *ray, t_interval t_ray, t_hit_record *record);
//Scene
void render_scene(t_control_panel *control_panel);
//antialiasing
void setup_antialiasing(t_control_panel *control_panel,int num_of_samples);
void sample_square(double out[3]);
//Camera
void get_values_camera(t_control_panel *control_panel);

//	Parsing.c
bool parsing(t_control_panel *control_panel, char *file_name);

//	Parse_elements.c
bool parse_amb_light(t_control_panel *control_panel, char **element_info, t_error_log *error_log);
bool parse_camera(t_control_panel *control_panel, char **element_info, t_error_log *error_log);
bool parse_light(t_control_panel *control_panel, char **element_info, t_error_log *error_log);

//	Parse_objects.c
bool parse_sphere(t_control_panel *control_panel, char **element_info, t_error_log *error_log);
bool parse_plane(t_control_panel *control_panel, char **element_info, t_error_log *error_log);
bool parse_cylinder(t_control_panel *control_panel, char **element_info, t_error_log *error_log);

//	Parse_values_1.c
bool get_coord(vec3 *coord, char *info, t_error_log *error_log);
bool get_vector(vec3 *vector, char *info, t_error_log *error_log);
bool get_rgb(double rgb[3], char *info, t_error_log *error_log);
bool	get_material(t_material *object_material, double rgb[3], char *info, t_error_log *error_log);

//	Parse_values_2.c
bool get_fov(mini_int *fov, char *info, t_error_log *error_log);
bool get_light_force(double *light_force, char *info, t_error_log *error_log);
bool get_brightness(float *brightness, char *info, t_error_log *error_log);
bool get_d(double *d, char *info, t_error_log *error_log);
bool get_height(double *height, char *info, t_error_log *error_log);

//	List_handler.c
void lstadd_last_sphere(t_control_panel *control_panel, t_sphere *new_sphere);
void lstadd_last_plane(t_control_panel *control_panel, t_plane *new_plane);
void lstadd_last_cylinder(t_control_panel *control_panel, t_cylinder *new_cylinder);

//	Free.c
void free_sphere(t_sphere *sphere);
void free_plane(t_plane *plane);
void free_cylinder(t_cylinder *cylinder);
void	free_control_panel_lists(t_control_panel *control_panel);

//	Utils.c
size_t double_array_len(char **array);
bool ft_atoc(const char *str, mini_int *dest);
bool ft_atofd(const char *str, void *dest, char type);
char **split_spaces(char const *s);

//	Extra -> Tests
void print_elements(t_control_panel *control_panel);

#endif
