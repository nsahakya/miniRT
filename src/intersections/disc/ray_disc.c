/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_disc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <david@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 00:00:00 by david             #+#    #+#             */
/*   Updated: 2026/05/11 00:00:00 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

bool	intersect_disc(t_ray ray, t_disc *disc, double *t)
{
	double	denom;
	double	t_hit;
	t_vec3	center_to_origin;
	t_vec3	point;
	t_vec3	dist_vec;

	denom = vec3_dot(ray.direction, disc->normal);
	if (denom > -0.0001 && denom < 0.0001)
		return (false);
	center_to_origin = vec3_add(disc->center, vec3_scale(ray.origin, -1));
	t_hit = vec3_dot(center_to_origin, disc->normal) / denom;
	if (t_hit <= 0.0001)
		return (false);
	point = vec3_add(ray.origin, vec3_scale(ray.direction, t_hit));
	dist_vec = vec3_add(point, vec3_scale(disc->center, -1));
	if (vec3_length(dist_vec) > disc->radius)
		return (false);
	*t = t_hit;
	return (true);
}