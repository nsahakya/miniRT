#include "../../../inc/miniRT.h"

bool	intersect_triangle(t_ray ray, t_triangle *triangle, double *t)
{
	t_vec3	edge1;
	t_vec3	edge2;
	t_vec3	h;
	t_vec3	s;
	t_vec3	q;
	double	a;
	double	f;
	double	u;
	double	v;

	edge1 = vec3_add(triangle->p2, vec3_scale(triangle->p1, -1));
	edge2 = vec3_add(triangle->p3, vec3_scale(triangle->p1, -1));
	h = vec3_cross(ray.direction, edge2);
	a = vec3_dot(edge1, h);
	if (a > -0.0001 && a < 0.0001)
		return (false);
	f = 1.0 / a;
	s = vec3_add(ray.origin, vec3_scale(triangle->p1, -1));
	u = f * vec3_dot(s, h);
	if (u < 0.0 || u > 1.0)
		return (false);
	q = vec3_cross(s, edge1);
	v = f * vec3_dot(ray.direction, q);
	if (v < 0.0 || u + v > 1.0)
		return (false);
	*t = f * vec3_dot(edge2, q);
	if (*t <= 0.0001)
		return (false);
	return (true);
}