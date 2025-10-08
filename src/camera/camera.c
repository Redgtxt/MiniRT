#include "../../includes/miniRT.h"

static void setup_camera_dimensions(t_control_panel *control_panel)
{
	control_panel->camera.aspect_ratio = 16.0 / 9.0;
	setup_antialiasing(control_panel,100);
	control_panel->camera.image_width = WINDOW_WIDTH;
	control_panel->camera.image_height = (int)control_panel->camera.image_width / control_panel->camera.aspect_ratio;
	if (control_panel->camera.image_height < 1)
	{
		control_panel->camera.image_height = 1;
	}
}
static void setup_camera_viewport(t_control_panel *control_panel)
{
    double focal_length;
    double viewport_height;
    double viewport_width;
    double viewport_u[3], viewport_v[3];
    double viewport_u_half[3], viewport_v_half[3];
    double viewport_upper_left[3], pixel_delta_sum[3], half_delta[3], temp[3];
    double theta;
    double h;
    double lookfrom_minus_lookat[3];


    vec3_copy(control_panel->camera.cords, control_panel->camera.cords);

    // Calculate lookfrom - lookat
    vec3_sub(lookfrom_minus_lookat, control_panel->camera.cords, control_panel->camera.lookat);

    // auto focal_length = (lookfrom - lookat).length();
    focal_length = vec3_lenght(lookfrom_minus_lookat);

    // FOV calculations
    theta = degrees_to_radians(control_panel->camera.fov);
    h = tan(theta / 2);
    viewport_height = 2.0 * h * focal_length;
    viewport_width = viewport_height * ((double)control_panel->camera.image_width / (double)control_panel->camera.image_height);

    // Calculate the u,v,w unit basis vectors for the camera coordinate frame
    // w = unit_vector(lookfrom - lookat);
    vec3_unit_vector(control_panel->camera.w, lookfrom_minus_lookat);

    // u = unit_vector(cross(vup, w));
    double cross_vup_w[3];
    vec3_cross(cross_vup_w, control_panel->camera.vup, control_panel->camera.w);
    vec3_unit_vector(control_panel->camera.u, cross_vup_w);

    // v = cross(w, u);
    vec3_cross(control_panel->camera.v, control_panel->camera.w, control_panel->camera.u);

    // Calculate the vectors across the horizontal and down the vertical viewport edges
    // vec3 viewport_u = viewport_width * u;
    vec3_scale(viewport_u, control_panel->camera.u, viewport_width);

    // vec3 viewport_v = viewport_height * -v;
    double neg_v[3];
    vec3_negate(neg_v, control_panel->camera.v);
    vec3_scale(viewport_v, neg_v, viewport_height);

    // Calculate the horizontal and vertical delta vectors from pixel to pixel
    vec3_divide(control_panel->camera.pixel_delta_u, viewport_u, (double)control_panel->camera.image_width);
    vec3_divide(control_panel->camera.pixel_delta_v, viewport_v, (double)control_panel->camera.image_height);

    // Calculate the location of the upper left pixel
    // auto viewport_upper_left = center - (focal_length * w) - viewport_u/2 - viewport_v/2;
    double focal_length_w[3];
    vec3_scale(focal_length_w, control_panel->camera.w, focal_length);
    vec3_divide(viewport_u_half, viewport_u, 2.0);
    vec3_divide(viewport_v_half, viewport_v, 2.0);

    // center - (focal_length * w) - viewport_u/2 - viewport_v/2
    vec3_sub(temp, control_panel->camera.cords, focal_length_w);
    vec3_sub(temp, temp, viewport_u_half);
    vec3_sub(viewport_upper_left, temp, viewport_v_half);

    // pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    vec3_add(pixel_delta_sum, control_panel->camera.pixel_delta_u, control_panel->camera.pixel_delta_v);
    vec3_scale(half_delta, pixel_delta_sum, 0.5);
    vec3_add(control_panel->camera.pixel00_loc, viewport_upper_left, half_delta);
}

void get_values_camera(t_control_panel *control_panel)
{
    setup_camera_dimensions(control_panel);
    // Setup lookat and vup before calling setup_camera_viewport
    vec3_add(control_panel->camera.lookat, control_panel->camera.cords, control_panel->camera.vec3);
    vec3_set(control_panel->camera.vup, 0, 1, 0);
    setup_camera_viewport(control_panel);
    control_panel->camera.max_bounces = MAX_CAMERA_BOUNCES;
}

/*
	Vertical fov
	começa em degrees e depois e convertido para radians


	lookfrom: posicao inical da camera
	lookat: ponto da cena onde a camera vai olhar
	vup:
	Orientaçao da camera

	Mesmo ambos os valores sendo estaticos ainda podes olhar a volta
	Tipo rodar a cabeça para ver ao redor

	vup(view up vector) indica o que e para cima

	w: vetor que vai de lookfrom para lookat,mas ao contrario do ponto de vista da camera (-w)
	u: vetor para a direita da camera
	v: vetor para cima da camera

	Lookfrom = posicao da camera
	lookat = posicao da camera + direcao da camera
	direcao da camera = -w(tenho de normalizar o valor)
*/
