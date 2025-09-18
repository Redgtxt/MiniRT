/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randrade <randrade@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:40:49 by randrade          #+#    #+#             */
/*   Updated: 2025/09/18 14:10:43 by randrade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H
#include "../Library/ft_printf/ft_printf.h"
#include "../Library/get_next_line/get_next_line.h"
#include "../Library/libft/libft.h"
#include "../Library/minilibx-linux/mlx.h"
#include "ui.h"
#include "vec3.h"
#include "interval.h"
#include "miniRT_error_p.h"
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <float.h>
#include <unistd.h>
#include <time.h> //BONUS

//	Printf colors
#define REDHB "\e[0;101m"
#define GRNHB "\e[0;102m"
#define reset "\e[0m"
#define BBLK "\e[1;30m"
#define BHGRN "\e[1;92m"
#define BHYEL "\e[1;93m"
#define HMAG "\e[1;95m"

// Light intensity control constants
#define DIFFUSE_INTENSITY 1.5  // Diffuse lighting multiplier (increased for brighter diffuse)
#define SPECULAR_INTENSITY 1.2 // Specular lighting multiplier (slightly increased for shinier highlights)
// Overall brightness control

// Light attenuation constants (realistic lighting)
#define LIGHT_CONSTANT 1.0	  // Base intensity
#define LIGHT_LINEAR 0.045	  // Linear falloff (reduced from 0.09 for brighter lights)
#define LIGHT_QUADRATIC 0.016 // Quadratic falloff (reduced from 0.032 for less distance falloff)

// // Light types for realistic lighting
// #define LIGHT_POINT      0  // Point light (current implementation)
// #define LIGHT_DIRECTIONAL 1  // Sun-like directional light
// #define LIGHT_SPOT       2  // Spotlight with cone
// #define LIGHT_AREA       3  // Area light (soft shadows)

// Alternative attenuation presets for different scenarios:
// Indoor lighting: constant=1.0, linear=0.09, quadratic=0.032
// Outdoor/Large spaces: constant=1.0, linear=0.014, quadratic=0.0007
// Close-range lighting: constant=1.0, linear=0.35, quadratic=0.44

#define PI 3.1415926535897932385
#define D_INFINITY ((double)INFINITY)

typedef unsigned char mini_int;
typedef double vec3;

typedef enum e_material_type
{
	LAMBERTIAN,
	METAL,
	CHECKERPATTERN,
	GLASS
} t_material_type;

typedef struct s_ray
{
	vec3 origin[3];

	double direction[3];

} t_ray;

typedef struct s_material
{
	t_material_type type;
	double albedo[3];
	double specular[3]; // Specular color
	double shininess;	// Specular exponent
	double checker_scale;
	double refraction_index; // Refractive index for glass materials
} t_material;

typedef struct s_data_scatter
{
	t_ray scattered;
	double attenuation[3];
} t_data_scatter;

typedef struct s_hit_record
{
	double position[3];
	double normal[3];
	double t;
	bool front_face;
	t_material *material;
} t_hit_record;

typedef struct s_data
{
	size_t amb_light_count;
	size_t camera_count;
	size_t light_count;
	size_t sphere_count;
	size_t plane_count;
	size_t cylinder_count;
	size_t cone_count;
	int obj_type; // Add this: 0 for sphere, 1 for plane, 2 for cylinder, 3 for cone
	int idx_obj;
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

	double lookat[3];
	double vup[3];

	double u[3];
	double v[3];
	double W[3];

	double max_bounces; // Maximum number of ray bounces into scene

	bool antialiasing;
} t_camera;

typedef struct s_light
{
	vec3 cords[3];
	double brightness;
	double rgb[3];
	double range;	  // Maximum effective range of the light (optional enhancement)
	int type;		  // Light type (LIGHT_POINT, LIGHT_DIRECTIONAL, etc.)
	double intensity; // Light intensity in lumens (real-world units)
	struct s_light *prev;
	struct s_light *next;
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
	t_material material;
	struct s_sphere *prev;
	struct s_sphere *next;
} t_sphere;

typedef struct s_plane
{
	//    PODE NAO SER O CENTRO (PELOS VISTOS PLANOS SAO INFINITOS)

	vec3 cords[3];

	vec3 vec3[3];

	double rgb[3];
	t_material material;
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
	t_material material;
	struct s_cylinder *prev;
	struct s_cylinder *next;
} t_cylinder;

typedef struct s_cone
{
	vec3 cords[3];
	vec3 vec3[3];
	double d;
	double radius;
	double height;
	double rgb[3];
	t_material material;
	struct s_cone *prev;
	struct s_cone *next;
} t_cone;

typedef struct s_control_panel
{
	t_amb_light amb_light;
	t_camera camera;
	t_light *light;
	t_sphere *sphere;
	t_plane *plane;
	t_cylinder *cylinder;
	t_cone *cone;
	t_data data;
	t_error_log error_log;
	t_mlx *mlx;
	t_win_config *config_win;
} t_control_panel;


/*Light*/
bool is_shadowed(t_control_panel *panel, vec3 point[3], t_light *light);
double get_shadow_intensity(t_control_panel *panel, vec3 point[3], t_light *light);
void diffuse_comp(t_light *light, t_hit_record *rec, vec3 color[3], vec3 light_dir[3], double attenuation);
/*Textures*/
bool scatter(const t_material *mat, const t_ray *r_in, t_hit_record *rec, t_data_scatter *data_scatter);

/*base_values*/
void	set_solid_material(t_material *material);
void	set_lambertian_material(t_material *material);
void	set_metal_material(t_material *material);
void	set_glass_material(t_material *material);
void	set_checker_material(t_material *material);

/*Ray functions*/
void init_ray(t_ray *ray);
void create_ray(t_ray *ray, const double origin[3], const double direction[3]);
void ray_origin(const t_ray *ray, double out[3]);
void ray_direction(const t_ray *ray, double out[3]);
void ray_at(double t, t_ray ray, double result[3]);
void ray_color(t_control_panel *control_panel, int depth, const t_ray *ray, double out_color[3]);
void vec3_normalize(double out[3], const double v[3]);
t_ray get_ray(int i, int j, t_control_panel *control_panel);

/*UITLS*/
double degrees_to_radians(double degrees);
double random_double_0_to_1();
double random_double(double min, double max);
int write_color(double r, double g, double b);
/*	sphere	*/

/*	Init	Sphere array	*/
bool linked_list_to_light_array(t_light **light_list, int size_array);
bool linked_list_to_sphere_array(t_sphere **sphere_list, int size_array);
bool linked_list_to_plane_array(t_plane **plane_list, int size_array);
bool linked_list_to_cylinder_array(t_cylinder **cylinder_list, int size_array);
bool linked_list_to_cone_array(t_cone **cone_list, int size_array);

/*Sphere Collision*/
bool hit_spheres(t_control_panel *scene, const t_ray *ray, t_interval t_ray, t_hit_record *record);
bool hit_world(t_control_panel *scene, const t_ray *ray, t_interval t_ray, t_hit_record *record);
void random_on_hemisphere(double normal[3], double out[3]);
void set_face_normal(const t_ray *ray, const double outward_normal[3], t_hit_record *record);
bool have_hit_sphere(t_sphere *sphere, const t_ray *ray, t_interval t_ray, t_hit_record *record);
// Planes
bool have_hit_plane(t_plane *plane, const t_ray *ray, t_interval t_ray, t_hit_record *record);
bool hit_planes(t_control_panel *scene, const t_ray *ray, t_interval t_ray, t_hit_record *record);

// Cylinder
bool have_hit_cylinder(t_cylinder *cylinder, const t_ray *ray, t_interval t_ray, t_hit_record *record);
bool hit_cylinders(t_control_panel *scene, const t_ray *ray, t_interval t_ray, t_hit_record *record);

double pont_dist(vec3 a[3], vec3 b[3]);
// Cone
bool hit_cones(t_control_panel *scene, const t_ray *ray, t_interval t_ray, t_hit_record *record);
bool have_hit_cone(t_cone *cone, const t_ray *ray, t_interval t_ray, t_hit_record *record);
// Scene
void render_scene(t_control_panel *cp);
// antialiasing
void setup_antialiasing(t_control_panel *control_panel, int num_of_samples);
void sample_square(double out[3]);
// Camera
void get_values_camera(t_control_panel *control_panel);
void move_camera_with_keys(int keycode, t_control_panel *cp);
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
bool parse_cone(t_control_panel *control_panel, char **element_info, t_error_log *error_log);

//	Parse_values_1.c
bool get_coord(vec3 *coord, char *info, t_error_log *error_log);
bool get_vector(vec3 *vector, char *info, t_error_log *error_log);
bool get_rgb(double rgb[3], char *info, t_error_log *error_log);
bool get_material(t_material *object_material, double rgb[3], char *info, t_error_log *error_log);

//	Parse_values_2.c
bool get_fov(mini_int *fov, char *info, t_error_log *error_log);
bool get_light_force(double *light_force, char *info, t_error_log *error_log);
bool get_brightness(double *brightness, char *info, t_error_log *error_log);
bool get_d(double *d, char *info, t_error_log *error_log);
bool get_height(double *height, char *info, t_error_log *error_log);

//	Linked_to_array.c
bool linked_to_array(t_control_panel *control_panel);

//	Init_object_seletion.c
void init_object_selection(t_control_panel *control_panel);

//	List_handler.c
void lstadd_last_light(t_control_panel *control_panel, t_light *new_light);
void lstadd_last_sphere(t_control_panel *control_panel, t_sphere *new_sphere);
void lstadd_last_plane(t_control_panel *control_panel, t_plane *new_plane);
void lstadd_last_cylinder(t_control_panel *control_panel, t_cylinder *new_cylinder);
void lstadd_last_cone(t_control_panel *control_panel, t_cone *new_cone);

//	Free.c
void free_light(t_light *light);
void free_sphere(t_sphere *sphere);
void free_plane(t_plane *plane);
void free_cylinder(t_cylinder *cylinder);
void free_cone(t_cone *cone);
void free_control_panel(t_control_panel *control_panel);

//	Utils.c
size_t double_array_len(char **array);
bool ft_atoc(const char *str, mini_int *dest);
bool ft_atofd(const char *str, void *dest, char type);
char **split_spaces(char const *s);

//	Extra -> Tests
void print_elements(t_control_panel *control_panel);

#endif
