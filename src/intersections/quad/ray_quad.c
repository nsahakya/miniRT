#include "../../../inc/miniRT.h"

static t_triangle	make_triangle(t_vec3 p1, t_vec3 p2, t_vec3 p3, t_rgb color)
{
	t_triangle	triangle;

	triangle.p1 = p1;
	triangle.p2 = p2;
	triangle.p3 = p3;
	triangle.color = color;
	return (triangle);
}

bool	intersect_quad(t_ray ray, t_quad *quad, double *t)
{
	t_triangle	tri1;
	t_triangle	tri2;
	double		t1;
	double		t2;
	bool		hit1;
	bool		hit2;

	tri1 = make_triangle(quad->p1, quad->p2, quad->p3, quad->color);
	tri2 = make_triangle(quad->p1, quad->p3, quad->p4, quad->color);
	hit1 = intersect_triangle(ray, &tri1, &t1);
	hit2 = intersect_triangle(ray, &tri2, &t2);
	if (hit1 && hit2)
	{
		if (t1 < t2)
			*t = t1;
		else
			*t = t2;
		return (true);
	}
	if (hit1)
	{
		*t = t1;
		return (true);
	}
	if (hit2)
	{
		*t = t2;
		return (true);
	}
	return (false);
} 