/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narek <narek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 21:42:48 by maghumya          #+#    #+#             */
/*   Updated: 2026/05/04 12:44:06 by narek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

static t_vec3	face_forward(t_vec3 n, t_vec3 ray_dir)
{
	if (vec3_dot(n, ray_dir) > 0.0)
		return (vec3_scale(n, -1.0));
	return (n);
}

t_vec3	get_plane_normal(t_plane *plane, t_vec3 point, t_vec3 ray_dir)
{
	(void)point;
	return (face_forward(vec3_normalize(plane->normal), ray_dir));
}

t_vec3	get_sphere_normal(t_sphere *sphere, t_vec3 point, t_vec3 ray_dir)
{
	t_vec3	normal;

	normal = vec3_subtract(point, sphere->center);
	return (face_forward(vec3_normalize(normal), ray_dir));
}

t_vec3	get_cylinder_normal(t_cylinder *cylinder, t_vec3 point, t_vec3 ray_dir)
{
	t_vec3	normal;
	t_vec3	center_to_point;
	double	proj_length;

	center_to_point = vec3_subtract(point, cylinder->center);
	proj_length = vec3_dot(center_to_point, cylinder->axis);
	if (fabs(proj_length - cylinder->half_height) < EPSILON)
		return (face_forward(vec3_normalize(cylinder->axis), ray_dir));
	else if (fabs(proj_length + cylinder->half_height) < EPSILON)
		return (face_forward(vec3_normalize(vec3_scale(cylinder->axis, -1)),
				ray_dir));
	normal = vec3_subtract(center_to_point, vec3_scale(cylinder->axis,
				proj_length));
	return (face_forward(vec3_normalize(normal), ray_dir));
}

t_vec3	get_cone_normal(t_cone *cone, t_vec3 point, t_vec3 ray_dir)
{
	t_vec3	x;
	double	m;
	double	k;
	double	k2;
	t_vec3	n;

	if (!cone)
		return ((t_vec3){0.0, 0.0, 0.0});
	x = vec3_subtract(point, cone->apex);
	m = vec3_dot(x, cone->axis);
	if (fabs(m - cone->height) < EPSILON)
		return (face_forward(vec3_normalize(cone->axis), ray_dir));
	k = cone->radius / cone->height;
	k2 = k * k;
	n = vec3_subtract(x, vec3_scale(cone->axis, (1.0 + k2) * m));
	return (face_forward(vec3_normalize(n), ray_dir));
}
t_vec3	get_box_normal(t_box *box, t_vec3 point, t_vec3 ray_dir)
{
	t_vec3	min_bound;
	t_vec3	max_bound;
	t_vec3	normal;
	double	eps;

	eps = 0.0001;
	min_bound.x = box->center.x - box->size.x / 2.0;
	min_bound.y = box->center.y - box->size.y / 2.0;
	min_bound.z = box->center.z - box->size.z / 2.0;
	max_bound.x = box->center.x + box->size.x / 2.0;
	max_bound.y = box->center.y + box->size.y / 2.0;
	max_bound.z = box->center.z + box->size.z / 2.0;
	normal = (t_vec3){0, 0, 0};
	if (fabs(point.x - min_bound.x) < eps)
		normal = (t_vec3){-1, 0, 0};
	else if (fabs(point.x - max_bound.x) < eps)
		normal = (t_vec3){1, 0, 0};
	else if (fabs(point.y - min_bound.y) < eps)
		normal = (t_vec3){0, -1, 0};
	else if (fabs(point.y - max_bound.y) < eps)
		normal = (t_vec3){0, 1, 0};
	else if (fabs(point.z - min_bound.z) < eps)
		normal = (t_vec3){0, 0, -1};
	else if (fabs(point.z - max_bound.z) < eps)
		normal = (t_vec3){0, 0, 1};
	return (face_forward(normal, ray_dir));
}