/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:40:49 by randrade          #+#    #+#             */
/*   Updated: 2025/10/02 15:36:33 by ruigoncalve      ###   ########.fr       */
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
// #include "hit_objects.h"
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <float.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <time.h> //BONUS

//	Printf colors
#define REDHB "\e[0;101m"
#define GRNHB "\e[0;102m"
#define BBLK "\e[1;30m"
#define BRED "\e[1;31m"
#define BHGRN "\e[1;92m"
#define BHYEL "\e[1;93m"
#define HMAG "\e[1;95m"
#define RESET "\e[0m"

#define MAX_CAMERA_BOUNCES 10

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

typedef enum e_mt_t
{
	LAMBERTIAN,
	METAL,
	CHECKERPATTERN,
	GLASS
} t_material_type;

typedef struct s_coord
{
	int x;
	int y;
} t_coord;

typedef struct s_ray
{
	vec3 origin[3];

	double direction[3];

} t_ray;

typedef struct s_mt
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

typedef struct s_cp
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

// ---- //
// RAY

typedef struct s_specular_args {
    t_hit_record *rec;
    const t_ray *ray;
    vec3 *light_dir;
    t_light *light;
    double attenuation;
} t_specular_args;

typedef struct s_light_args {
    t_control_panel *panel;
    t_hit_record *rec;
    const t_ray *ray;
    vec3 *color;
    size_t i;
} t_light_args;

typedef struct s_scatter_args {
    t_control_panel *panel;
    int depth;
    const t_ray *ray;
    t_hit_record *rec;
} t_scatter_args;

// ---- //

// ----- //
// shadow //

typedef struct s_intensity_args {
	t_control_panel *panel;
	t_light *light;
	double *light_distance;
	double *light_transmission;
} t_intensity_args;

typedef struct s_intensity_data {
	t_ray shadow_ray;
	vec3 light_dir[3];
	double light_distance;
	double light_transmission;
} t_intensity_data;

// ----- //
// reflect_types //

typedef struct s_refract_data {
	double uv_negated[3];
	double cos_theta;
	double cos_theta_n[3];
	double temp[3];
	double r_out_perp[3];
} t_refract_data;

//----- //


// --- Structs from cone_collision.c ---
typedef struct s_cone_cap_vars {
	double cap_center[3];
	double p_minus_o[3];
	double intersection_point[3];
	double dist_vec[3];
	double denom;
	double t;
} t_cone_cap_vars;

typedef struct s_cone_body_vars {
	double oc[3];
	double tan_theta;
	double k;
	double dot_d_v;
	double dot_oc_v;
	double a;
	double b;
	double c;
	double discriminant;
	double sqrt_d;
	double t1;
	double t2;
	double t;
	double m1;
	double m2;
	double m;
	double temp[3];
	double normal[3];
	double p_minus_c[3];
	double cone_tip[3];
} t_cone_body_vars;

// --- Structs from cylinder_collision.c ---
typedef struct s_cylinder_body_vars {
	vec3 axis[3];
	vec3 oc[3];
	double dir_dot_axis;
	double oc_dot_axis;
	vec3 dir_parallel[3];
	vec3 dir_perp[3];
	vec3 oc_parallel[3];
	vec3 oc_perp[3];
	double a;
	double b;
	double c;
	double discriminant;
	double sqrt_disc;
	double t1;
	double t2;
	double t;
	vec3 hit_point[3];
	vec3 hit_vec[3];
	double hit_height;
	vec3 cp[3];
	vec3 outward_normal[3];
} t_cylinder_body_vars;

typedef struct s_cylinder_cap_vars {
	double denom;
	double p0l0[3];
	double t;
	vec3 normalized_axis[3];
	double outward_normal[3];
} t_cylinder_cap_vars;

typedef struct s_have_hit_cylinder_vars {
	bool hit_anything;
	double closest_so_far;
	t_hit_record temp_rec;
	t_cylinder *cylinder;
	t_cylinder original_cylinder;
	double original_rgb[3];
	vec3 axis[3];
} t_have_hit_cylinder_vars;

// --- Structs from plane_collisions.c ---
typedef struct s_plane_vars {
	double denom;
	double p0l0[3];
	double t;
} t_plane_vars;

// --- Structs from sphere_collision.c ---
typedef struct s_sphere_vars {
	double oc[3];
	double a;
	double h;
	double c;
	double discriminant;
	double root;
} t_sphere_vars;

// --- Function prototypes ---
bool have_hit_cone(t_cone *cone, const t_ray *ray, t_interval t_ray, t_hit_record *record);
bool hit_cones(t_control_panel *scene, const t_ray *ray, t_interval t_ray, t_hit_record *record);
bool have_hit_cylinder(t_cylinder *cylinder, const t_ray *ray, t_interval t_ray, t_hit_record *record);
bool hit_cylinders(t_control_panel *scene, const t_ray *ray, t_interval t_ray, t_hit_record *record);
bool have_hit_plane(t_plane *plane, const t_ray *ray, t_interval t_ray, t_hit_record *record);
bool hit_planes(t_control_panel *scene, const t_ray *ray, t_interval t_ray, t_hit_record *record);
bool have_hit_sphere(t_sphere *sphere, const t_ray *ray, t_interval t_ray, t_hit_record *record);
bool hit_spheres(t_control_panel *scene, const t_ray *ray, t_interval t_ray, t_hit_record *record);
bool hit_world(t_control_panel *scene, const t_ray *ray, t_interval t_ray, t_hit_record *record);
void random_on_hemisphere(double normal[3], double out[3]);

/*Light*/
double get_shadow_intensity(t_control_panel *panel, vec3 point[3], t_light *light);
void diffuse_comp(t_light_args *args, vec3 light_dir[3], double attenuation);
void process_light(t_light_args *args);
void set_amb_light(t_control_panel *control_panel, const t_ray *ray, double out_color[3]);
void init_spec_args(t_specular_args *spec_args, t_light_args *args, vec3 light_dir[3], double attenuation);
void add_specular(t_specular_args *args, vec3 color[3]);
/*Textures*/
bool scatter(const t_material *mat, const t_ray *r_in, t_hit_record *rec, t_data_scatter *data_scatter);
//	Lambertian
bool lambertian_scatter(t_hit_record *rec, t_data_scatter *data_scatter);
//	Metal
bool metal_scatter(const t_ray *r_in, t_hit_record *rec, t_data_scatter *data_scatter);
//	Glass
bool glass_scatter(const t_ray *r_in, t_hit_record *rec, t_data_scatter *data_scatter);
//	CheckerPattern
bool checker_scatter(t_hit_record *rec, t_data_scatter *data_scatter);

/*base_values*/
void	set_lambertian_material(t_material *material, double rgb[3]);
void	set_metal_material(t_material *material, double rgb[3]);
void	set_glass_material(t_material *material);
void	set_checker_material(t_material *material, double rgb[3]);

/*Ray functions*/
void init_ray(t_ray *ray);
void create_ray(t_ray *ray, const double origin[3], const double direction[3]);
void ray_origin(const t_ray *ray, double out[3]);
void ray_direction(const t_ray *ray, double out[3]);
void ray_at(double t, t_ray ray, double result[3]);
void ray_color(t_control_panel *control_panel, int depth, const t_ray *ray, double out_color[3]);
void vec3_normalize(double out[3], const double v[3]);
t_ray get_ray(t_coord coord, t_control_panel *control_panel);

/*UITLS*/
double	lenght_squared(const double vector[3]);
double degrees_to_radians(double degrees);
double random_double_0_to_1();
double random_double(double min, double max);
int write_color(double r, double g, double b);
void	calc_perpendicular(t_refract_data *data, const double uv[3], const double n[3], double etai_over_etat);
void	calc_parallel(double r_out_parallel[3], const double n[3], double r_out_perp[3]);

/*	sphere	*/

/*	Init	Sphere array	*/
bool linked_list_to_light_array(t_light **light_list, int size_array);
bool linked_list_to_sphere_array(t_sphere **sphere_list, int size_array);
bool linked_list_to_plane_array(t_plane **plane_list, int size_array);
bool linked_list_to_cylinder_array(t_cylinder **cylinder_list, int size_array);
bool linked_list_to_cone_array(t_cone **cone_list, int size_array);

/*Sphere Collision*/
void set_hit_record(bool *hit, double *closest_so_far, t_hit_record *record, t_hit_record *temp_rec);
bool hit_spheres(t_control_panel *scene, const t_ray *ray, t_interval t_ray, t_hit_record *record);
bool hit_world(t_control_panel *scene, const t_ray *ray, t_interval t_ray, t_hit_record *record);
void random_on_hemisphere(double normal[3], double out[3]);
void set_face_normal(const t_ray *ray, const double outward_normal[3], t_hit_record *record);
bool have_hit_sphere(t_sphere *sphere, const t_ray *ray, t_interval t_ray, t_hit_record *record);

// Planes
bool hit_planes(t_control_panel *scene, const t_ray *ray, t_interval t_ray, t_hit_record *record);

// Cylinder
bool hit_cylinders(t_control_panel *scene, const t_ray *ray, t_interval t_ray, t_hit_record *record);

// Cylinder body
bool hit_cylinder_body(t_cylinder *cylinder, const t_ray *ray, t_interval t_ray, t_hit_record *record);

// Cylinder caps
bool have_hit_cylinder_cap(t_cylinder *cylinder, const t_ray *ray, t_interval t_ray, t_hit_record *record);

// Cylinder utils
double	pont_dist(vec3 a[3], vec3 b[3]);
void	init_cylinder_cap_vars(t_cylinder_cap_vars *vars, t_cylinder *cylinder, const t_ray *ray);
void 	init_cylinder_body_vars(t_cylinder_body_vars *vars, t_cylinder *cylinder, const t_ray *ray);
void	init_have_hit_cylinder_struct(t_have_hit_cylinder_vars *vars, t_cylinder *cylinder, t_interval t_ray);

// Cone
bool hit_cones(t_control_panel *scene, const t_ray *ray, t_interval t_ray, t_hit_record *record);
bool have_hit_cone(t_cone *cone, const t_ray *ray, t_interval t_ray, t_hit_record *record);

// Cone cap
bool have_hit_cone_cap(t_cone *cone, const t_ray *ray, t_interval t_ray, t_hit_record *record);

// Cone body
bool hit_cone_body(t_cone *cone, const t_ray *ray, t_interval t_ray, t_hit_record *record);

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
bool get_size(double *d, char *info, t_error_log *error_log);

//	Parse_values_utils.c
bool parse_numbers(char *info, size_t *nbr_dot, t_error_log *error_log, bool negative);
bool parse_three_octet_values(char *info, t_error_log *error_log);
bool parse_rgb_chars(char *info, t_error_log *error_log);
bool parse_number_elements(t_data data, t_error_log *error_log);

//	Initialization.c
bool linked_to_array(t_control_panel *control_panel);
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
bool ft_atod(const char *str, double *dest);
char **split_spaces(char const *s);

//	Extra -> Tests
void print_elements(t_control_panel *control_panel);

#endif
