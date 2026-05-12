/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsahakya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 18:20:07 by nsahakya          #+#    #+#             */
/*   Updated: 2026/02/06 18:20:08 by nsahakya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

bool	cylinder_body_hit(t_ray ray, t_cylinder *cylinder, double *t_hit)
{
	t_cy_body	body;
	t_vec3		point;
	double		axis_pos;

	cylinder_body_init(&body, ray, cylinder);
	if (!cylinder_body_solve(&body))
		return (false);
	point = ray_point_at(ray, body.t0);
	axis_pos = vec3_dot(vec3_subtract(point, cylinder->center), cylinder->axis);
	if (body.t0 > EPSILON && axis_pos >= -cylinder->half_height
		&& axis_pos <= cylinder->half_height)
		return (*t_hit = body.t0, true);
	point = ray_point_at(ray, body.t1);
	axis_pos = vec3_dot(vec3_subtract(point, cylinder->center), cylinder->axis);
	if (body.t1 > EPSILON && axis_pos >= -cylinder->half_height
		&& axis_pos <= cylinder->half_height)
		return (*t_hit = body.t1, true);
	return (false);
}

static void	intersect_check(bool *hit, double t_disk, double *closest_t)
{
	if (!*hit || t_disk < *closest_t)
		*closest_t = t_disk;
	*hit = true;
}

bool	cylinder_disk_hit(t_ray ray, t_cylinder *cy, double *t_hit)
{
	t_disk	disk;
	double	closest_t;
	double	t_disk_t;
	bool	hit;

	if (!t_hit)
		return (false);
	hit = false;
	disk.center = vec3_add(cy->center, vec3_scale(cy->axis, cy->half_height));
	disk.normal = cy->axis;
	disk.radius = cy->radius;
	if (intersect_disk(ray, disk, &t_disk_t))
	{
		closest_t = t_disk_t;
		hit = true;
	}
	disk.center = vec3_subtract(cy->center, vec3_scale(cy->axis,
				cy->half_height));
	disk.normal = vec3_scale(cy->axis, -1.0);
	if (intersect_disk(ray, disk, &t_disk_t))
		intersect_check(&hit, t_disk_t, &closest_t);
	if (!hit)
		return (false);
	*t_hit = closest_t;
	return (true);
}

// ...existing code...

bool	intersect_disk(t_ray ray, t_disk disk, double *t_hit)
{
	t_disk_intersect	d;

	if (!t_hit)
		return (false);
	d.denom = vec3_dot(ray.direction, disk.normal);
	if (fabs(d.denom) < EPSILON)
		return (false);
	d.t = vec3_dot(vec3_subtract(disk.center, ray.origin), disk.normal)
		/ d.denom;
	if (d.t <= EPSILON)
		return (false);
	d.p = ray_point_at(ray, d.t);
	d.v = vec3_subtract(d.p, disk.center);
	d.in_plane = vec3_subtract(d.v, project_on_axis(d.v, disk.normal));
	d.dist_square = vec3_length_squared(d.in_plane);
	if (d.dist_square > disk.radius * disk.radius)
		return (false);
	*t_hit = d.t;
	return (true);
}

