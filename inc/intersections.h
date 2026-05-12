/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narek <narek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 18:35:58 by nsahakya          #+#    #+#             */
/*   Updated: 2026/05/04 12:41:13 by narek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTIONS_H
# define INTERSECTIONS_H

# include "scene.h"
# include <stdbool.h>

typedef struct s_hit_record
{
	bool	hit;
	double	t;
	t_vec3	point;
	t_vec3	normal;
	t_rgb	color;
}			t_hit_record;

typedef struct s_sphere_intersect
{
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	sqrt_d;
	double	t0;
	double	t1;
}			t_sphere_intersect;

typedef struct s_disk_intersect
{
	double	denom;
	double	t;
	t_vec3	p;
	t_vec3	v;
	t_vec3	in_plane;
	double	dist_square;
}			t_disk_intersect;

typedef struct s_disk
{
	t_vec3	center;
	t_vec3	normal;
	double	radius;
}			t_disk;

typedef struct s_cy_body
{
	t_vec3	oc;
	double	d_dot_a;
	double	oc_dot_a;
	t_vec3	d_perp;
	t_vec3	oc_perp;
	double	a;
	double	b;
	double	c;
	double	disc;
	double	sqrt_disc;
	double	t0;
	double	t1;
}			t_cy_body;

typedef struct s_cone_side
{
	t_vec3	w;
    double	k;
    double	k2;
    double	dv;
    double	wv;
    t_vec3	d_perp;
    t_vec3	w_perp;
    double	a, b, c;
    double	disc, sqrt_disc;
    double	t0, t1;
    double	m;
}	t_cone_side;

bool		intersect_sphere(t_ray ray, t_sphere *sphere, double *t);
bool		intersect_plane(t_ray ray, t_plane *plane, double *t);
bool		intersect_cylinder(t_ray ray, t_cylinder *cylinder, double *t);
bool		intersect_cone(t_ray ray, t_cone *cone, double *t);
bool		intersect_box(t_ray ray, t_box *box, double *t);

bool		find_closest_intersection(t_ray ray, t_scene *scene,
				t_hit_record *rec);

/*utils*/

/*cylinder*/
t_vec3		ray_point_at(t_ray ray, double t);
t_vec3		project_on_axis(t_vec3 v, t_vec3 axis);
void		cylinder_body_init(t_cy_body *b, t_ray ray, t_cylinder *cylinder);
bool		cylinder_body_solve(t_cy_body *b);
bool		cylinder_body_hit(t_ray ray, t_cylinder *cylinder, double *t_hit);
bool		cylinder_disk_hit(t_ray ray, t_cylinder *cylinder, double *t_hit);
bool		intersect_disk(t_ray ray, t_disk disk, double *t_hit);

/* normals */
t_vec3		get_plane_normal(t_plane *plane, t_vec3 point, t_vec3 ray_dir);
t_vec3		get_sphere_normal(t_sphere *sphere, t_vec3 point, t_vec3 ray_dir);
t_vec3		get_cylinder_normal(t_cylinder *cylinder, t_vec3 point,
				t_vec3 ray_dir);
t_vec3		get_cone_normal(t_cone *cone, t_vec3 point, t_vec3 ray_dir);
t_vec3		get_box_normal(t_box *box, t_vec3 point, t_vec3 ray_dir);

#endif
