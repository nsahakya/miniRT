/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_box.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 00:00:00 by david             #+#    #+#             */
/*   Updated: 2026/05/11 00:00:00 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

static void	swap_double(double *a, double *b)
{
	double	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static double	get_min(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}

static double	get_max(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

static bool	check_axis(double origin, double direction,
		double min_bound, double max_bound, double *t_range)
{
	double	t1;
	double	t2;

	if (direction > -0.000001 && direction < 0.000001)
	{
		if (origin < min_bound || origin > max_bound)
			return (false);
		return (true);
	}
	t1 = (min_bound - origin) / direction;
	t2 = (max_bound - origin) / direction;
	if (t1 > t2)
		swap_double(&t1, &t2);
	t_range[0] = get_max(t_range[0], t1);
	t_range[1] = get_min(t_range[1], t2);
	if (t_range[0] > t_range[1])
		return (false);
	return (true);
}

bool	intersect_box(t_ray ray, t_box *box, double *t)
{
	t_vec3	min_bound;
	t_vec3	max_bound;
	double	t_range[2];

	min_bound.x = box->center.x - box->size.x / 2.0;
	min_bound.y = box->center.y - box->size.y / 2.0;
	min_bound.z = box->center.z - box->size.z / 2.0;
	max_bound.x = box->center.x + box->size.x / 2.0;
	max_bound.y = box->center.y + box->size.y / 2.0;
	max_bound.z = box->center.z + box->size.z / 2.0;
	t_range[0] = -1e30;
	t_range[1] = 1e30;
	if (!check_axis(ray.origin.x, ray.direction.x,
			min_bound.x, max_bound.x, t_range))
		return (false);
	if (!check_axis(ray.origin.y, ray.direction.y,
			min_bound.y, max_bound.y, t_range))
		return (false);
	if (!check_axis(ray.origin.z, ray.direction.z,
			min_bound.z, max_bound.z, t_range))
		return (false);
	if (t_range[1] < 0.0001)
		return (false);
	if (t_range[0] > 0.0001)
		*t = t_range[0];
	else
		*t = t_range[1];
	return (true);
}