/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest_intersection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narek <narek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 18:19:48 by nsahakya          #+#    #+#             */
/*   Updated: 2026/05/04 12:44:06 by narek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/miniRT.h"

static void	check_sphere_intersections(t_ray ray, t_list *spheres,
		double *best_t, t_hit_record *rec)
{
	t_list		*node;
	t_sphere	*sp;
	double		t;

	node = spheres;
	while (node)
	{
		sp = (t_sphere *)node->content;
		if (intersect_sphere(ray, sp, &t) && t < *best_t)
		{
			*best_t = t;
			rec->hit = true;
			rec->t = t;
			rec->point = vec3_add(ray.origin, vec3_scale(ray.direction, t));
			rec->normal = get_sphere_normal(sp, rec->point, ray.direction);
			rec->color = sp->color;
		}
		node = node->next;
	}
}

static void	check_plane_intersections(t_ray ray, t_list *planes, double *best_t,
		t_hit_record *rec)
{
	t_list	*node;
	t_plane	*pl;
	double	t;

	node = planes;
	while (node)
	{
		pl = (t_plane *)node->content;
		if (intersect_plane(ray, pl, &t) && t < *best_t)
		{
			*best_t = t;
			rec->hit = true;
			rec->t = t;
			rec->point = vec3_add(ray.origin, vec3_scale(ray.direction, t));
			rec->normal = get_plane_normal(pl, rec->point, ray.direction);
			rec->color = pl->color;
		}
		node = node->next;
	}
}

static void	check_cylinder_intersections(t_ray ray, t_list *cylinders,
		double *best_t, t_hit_record *rec)
{
	t_list		*node;
	t_cylinder	*cy;
	double		t;

	node = cylinders;
	while (node)
	{
		cy = (t_cylinder *)node->content;
		if (intersect_cylinder(ray, cy, &t) && t < *best_t)
		{
			*best_t = t;
			rec->hit = true;
			rec->t = t;
			rec->point = vec3_add(ray.origin, vec3_scale(ray.direction, t));
			rec->normal = get_cylinder_normal(cy, rec->point, ray.direction);
			rec->color = cy->color;
		}
		node = node->next;
	}
}

static void	check_cone_intersections(t_ray ray, t_list *cones,
		double *best_t, t_hit_record *rec)
{
	t_list	*node;
	t_cone	*co;
	double	t;

	node = cones;
	while (node)
	{
		co = (t_cone *)node->content;
		if (intersect_cone(ray, co, &t) && t < *best_t)
		{
			*best_t = t;
			rec->hit = true;
			rec->t = t;
			rec->point = vec3_add(ray.origin, vec3_scale(ray.direction, t));
			rec->normal = get_cone_normal(co, rec->point, ray.direction);
			rec->color = co->color;
		}
		node = node->next;
	}
}

bool	find_closest_intersection(t_ray ray, t_scene *scene, t_hit_record *rec)
{
	double	best_t;

	if (!scene || !rec)
		return (false);
	rec->hit = false;
	best_t = DBL_MAX;
	check_sphere_intersections(ray, scene->spheres, &best_t, rec);
	check_plane_intersections(ray, scene->planes, &best_t, rec);
	check_cylinder_intersections(ray, scene->cylinders, &best_t, rec);
	check_cone_intersections(ray, scene->cones, &best_t, rec);
	return (rec->hit);
}
