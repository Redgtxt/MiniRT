#include "../../includes/miniRT.h"

void	vec3_add_scaled(double out[3], const double a[3], const double b[3],
		double s)
{
	double	scaled_b[3];

	vec3_scale(scaled_b, b, s);
	vec3_add(out, a, scaled_b);
}

double	vec3_length_squared(const double v[3])
{
	return (v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}
