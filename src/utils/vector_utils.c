#include "../../includes/miniRT.h"

void vec3_set(double v[3], double x, double y, double z)
{
	v[0] = x;
	v[1] = y;
	v[2] = z;
}

void vec3_copy(double dest[3], const double src[3])
{
	dest[0] = src[0];
	dest[1] = src[1];
	dest[2] = src[2];
}

void vec3_scale(double out[3], const double v[3], double s)
{
	out[0] = v[0] * s;
	out[1] = v[1] * s;
	out[2] = v[2] * s;
}

void vec3_add(double out[3], const double a[3], const double b[3])
{
	out[0] = a[0] + b[0];
	out[1] = a[1] + b[1];
	out[2] = a[2] + b[2];
}

void vec3_sub(double out[3], const double a[3], const double b[3])
{
	out[0] = a[0] - b[0];
	out[1] = a[1] - b[1];
	out[2] = a[2] - b[2];
}
double vec3_dot(const double a[3], const double b[3])
{
    return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}

