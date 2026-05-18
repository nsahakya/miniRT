/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narek <narek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 18:06:52 by maghumya          #+#    #+#             */
/*   Updated: 2026/05/04 12:33:42 by narek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

bool	parse_sphere(char **tokens, t_scene *scene)
{
	t_sphere	*sphere;
	t_list		*new_sphere_node;

	sphere = ft_calloc(1, sizeof(t_sphere));
	if (!sphere)
		return (put_error("Memory allocation failed"));
	if (!check_split_length(tokens, 4))
		return (free(sphere), put_error("Invalid sphere definition"));
	if (!parse_vec3(tokens[1], &sphere->center))
		return (free(sphere), false);
	if (!check_double(tokens[2]))
		return (free(sphere), put_error("Invalid sphere diameter"));
	sphere->radius = ft_atod(tokens[2]) / 2.0;
	if (sphere->radius <= 0)
		return (free(sphere), put_error("Sphere radius must be positive"));
	if (!parse_rgb(tokens[3], &sphere->color))
		return (free(sphere), false);
	new_sphere_node = ft_lstnew(sphere);
	if (!new_sphere_node)
		return (free(sphere), put_error("Memory allocation failed"));
	ft_lstadd_back(&scene->spheres, new_sphere_node);
	return (true);
}

bool	parse_plane(char **tokens, t_scene *scene)
{
	t_plane	*plane;
	t_list	*new_plane_node;

	plane = ft_calloc(1, sizeof(t_plane));
	if (!plane)
		return (put_error("Memory allocation failed"));
	if (!check_split_length(tokens, 4))
		return (free(plane), put_error("Invalid plane definition"));
	if (!parse_vec3(tokens[1], &plane->point))
		return (free(plane), false);
	if (!parse_vec3(tokens[2], &plane->normal))
		return (free(plane), false);
	if (!check_range_vec3(plane->normal, -1.0, 1.0))
		return (free(plane),
			put_error("Plane normal vector must be in range [-1,1]"));
	if (vec3_length(plane->normal) < 0.0001)
		return (free(plane), put_error("Direction cannot be zero"));
	plane->normal = vec3_normalize(plane->normal);
	if (!parse_rgb(tokens[3], &plane->color))
		return (free(plane), false);
	new_plane_node = ft_lstnew(plane);
	if (!new_plane_node)
		return (free(plane), put_error("Memory allocation failed"));
	ft_lstadd_back(&scene->planes, new_plane_node);
	return (true);
}

static bool	parse_cylinder_args(char **tokens, t_cylinder *cylinder)
{
	if (!parse_vec3(tokens[1], &cylinder->center))
		return (false);
	if (!parse_vec3(tokens[2], &cylinder->axis))
		return (false);
	if (!check_range_vec3(cylinder->axis, -1.0, 1.0))
		return (put_error("Cylinder axis vector must be in range [-1,1]"));
	if (vec3_length(cylinder->axis) < 0.0001)
		return (put_error("Direction cannot be zero"));
	cylinder->axis = vec3_normalize(cylinder->axis);
	if (!check_double(tokens[3]) || !check_double(tokens[4]))
		return (put_error("Invalid cylinder dimensions"));
	cylinder->radius = ft_atod(tokens[3]) / 2.0;
	cylinder->half_height = ft_atod(tokens[4]) / 2.0;
	if (cylinder->radius <= 0 || cylinder->half_height <= 0)
		return (put_error("Cylinder diameter and height must be positive"));
	if (!parse_rgb(tokens[5], &cylinder->color))
		return (false);
	return (true);
}

bool	parse_cylinder(char **tokens, t_scene *scene)
{
	t_cylinder	*cylinder;
	t_list		*new_cylinder_node;

	cylinder = ft_calloc(1, sizeof(t_cylinder));
	if (!cylinder)
		return (put_error("Memory allocation failed"));
	if (!check_split_length(tokens, 6))
		return (free(cylinder), put_error("Invalid cylinder definition"));
	if (!parse_cylinder_args(tokens, cylinder))
		return (free(cylinder), false);
	new_cylinder_node = ft_lstnew(cylinder);
	if (!new_cylinder_node)
		return (free(cylinder), put_error("Memory allocation failed"));
	ft_lstadd_back(&scene->cylinders, new_cylinder_node);
	return (true);
}

static bool	parse_cone_args(char **tokens, t_cone *cone)
{
	if (!parse_vec3(tokens[1], &cone->apex))
		return (false);
	if (!parse_vec3(tokens[2], &cone->axis))
		return (false);
	if (!check_range_vec3(cone->axis, -1.0, 1.0))
		return (put_error("Cone axis vector must be in range [-1,1]"));
	if (vec3_length(cone->axis) < 0.0001)
		return (put_error("Direction cannot be zero"));
	cone->axis = vec3_normalize(cone->axis);
	if (!check_double(tokens[3]) || !check_double(tokens[4]))
		return (put_error("Invalid cone dimensions"));
	cone->radius = ft_atod(tokens[3]) / 2.0;
	cone->height = ft_atod(tokens[4]);
	if (cone->radius <= 0.0 || cone->height <= 0.0)
		return (put_error("Cone diameter and height must be positive"));
	if (!parse_rgb(tokens[5], &cone->color))
		return (false);
	return (true);
}

bool	parse_cone(char **tokens, t_scene *scene)
{
	t_cone	*cone;
	t_list	*node;

	cone = ft_calloc(1, sizeof(t_cone));
	if (!cone)
		return (put_error("Memory allocation failed"));
	if (!check_split_length(tokens, 6))
		return (free(cone), put_error("Invalid cone definition"));
	if (!parse_cone_args(tokens, cone))
		return (free(cone), false);
	node = ft_lstnew(cone);
	if (!node)
		return (free(cone), put_error("Memory allocation failed"));
	ft_lstadd_back(&scene->cones, node);
	return (true);
}
static bool	parse_box_args(char **tokens, t_box *box)
{
	if (!parse_vec3(tokens[1], &box->center))
		return (false);
	if (!parse_vec3(tokens[2], &box->size))
		return (false);
	if (box->size.x <= 0.0 || box->size.y <= 0.0 || box->size.z <= 0.0)
		return (put_error("Box dimensions must be positive"));
	if (!parse_rgb(tokens[3], &box->color))
		return (false);
	return (true);
}

bool	parse_box(char **tokens, t_scene *scene)
{
	t_box	*box;
	t_list	*node;

	box = ft_calloc(1, sizeof(t_box));
	if (!box)
		return (put_error("Memory allocation failed"));
	if (!check_split_length(tokens, 4))
		return (free(box), put_error("Invalid box definition"));
	if (!parse_box_args(tokens, box))
		return (free(box), false);
	node = ft_lstnew(box);
	if (!node)
		return (free(box), put_error("Memory allocation failed"));
	ft_lstadd_back(&scene->boxes, node);
	return (true);
}

static bool	parse_triangle_args(char **tokens, t_triangle *triangle)
{
	t_vec3	edge1;
	t_vec3	edge2;
	t_vec3	normal;

	if (!parse_vec3(tokens[1], &triangle->p1))
		return (false);
	if (!parse_vec3(tokens[2], &triangle->p2))
		return (false);
	if (!parse_vec3(tokens[3], &triangle->p3))
		return (false);
	edge1 = vec3_add(triangle->p2, vec3_scale(triangle->p1, -1));
	edge2 = vec3_add(triangle->p3, vec3_scale(triangle->p1, -1));
	normal = vec3_cross(edge1, edge2);
	if (vec3_length(normal) < 0.0001)
		return (put_error("Triangle points must not be collinear"));
	if (!parse_rgb(tokens[4], &triangle->color))
		return (false);
	return (true);
}

bool	parse_triangle(char **tokens, t_scene *scene)
{
	t_triangle	*triangle;
	t_list		*node;

	triangle = ft_calloc(1, sizeof(t_triangle));
	if (!triangle)
		return (put_error("Memory allocation failed"));
	if (!check_split_length(tokens, 5))
		return (free(triangle), put_error("Invalid triangle definition"));
	if (!parse_triangle_args(tokens, triangle))
		return (free(triangle), false);
	node = ft_lstnew(triangle);
	if (!node)
		return (free(triangle), put_error("Memory allocation failed"));
	ft_lstadd_back(&scene->triangles, node);
	return (true);
}

static bool	parse_disc_args(char **tokens, t_disc *disc)
{
	if (!parse_vec3(tokens[1], &disc->center))
		return (false);
	if (!parse_vec3(tokens[2], &disc->normal))
		return (false);
	if (!check_range_vec3(disc->normal, -1.0, 1.0))
		return (put_error("Disc normal vector must be in range [-1,1]"));
	if (vec3_length(disc->normal) < 0.0001)
		return (put_error("Direction cannot be zero"));
	disc->normal = vec3_normalize(disc->normal);
	if (!check_double(tokens[3]))
		return (put_error("Invalid disc diameter"));
	disc->radius = ft_atod(tokens[3]) / 2.0;
	if (disc->radius <= 0.0)
		return (put_error("Disc diameter must be positive"));
	if (!parse_rgb(tokens[4], &disc->color))
		return (false);
	return (true);
}

bool	parse_disc(char **tokens, t_scene *scene)
{
	t_disc	*disc;
	t_list	*node;

	disc = ft_calloc(1, sizeof(t_disc));
	if (!disc)
		return (put_error("Memory allocation failed"));
	if (!check_split_length(tokens, 5))
		return (free(disc), put_error("Invalid disc definition"));
	if (!parse_disc_args(tokens, disc))
		return (free(disc), false);
	node = ft_lstnew(disc);
	if (!node)
		return (free(disc), put_error("Memory allocation failed"));
	ft_lstadd_back(&scene->discs, node);
	return (true);
}
static bool	check_quad_points(t_quad *quad)
{
	t_vec3	edge1;
	t_vec3	edge2;
	t_vec3	normal;

	edge1 = vec3_add(quad->p2, vec3_scale(quad->p1, -1));
	edge2 = vec3_add(quad->p3, vec3_scale(quad->p1, -1));
	normal = vec3_cross(edge1, edge2);
	if (vec3_length(normal) < 0.0001)
		return (put_error("Quad first triangle points are invalid"));
	edge1 = vec3_add(quad->p3, vec3_scale(quad->p1, -1));
	edge2 = vec3_add(quad->p4, vec3_scale(quad->p1, -1));
	normal = vec3_cross(edge1, edge2);
	if (vec3_length(normal) < 0.0001)
		return (put_error("Quad second triangle points are invalid"));
	return (true);
}

static bool	parse_quad_args(char **tokens, t_quad *quad)
{
	if (!parse_vec3(tokens[1], &quad->p1))
		return (false);
	if (!parse_vec3(tokens[2], &quad->p2))
		return (false);
	if (!parse_vec3(tokens[3], &quad->p3))
		return (false);
	if (!parse_vec3(tokens[4], &quad->p4))
		return (false);
	if (!check_quad_points(quad))
		return (false);
	if (!parse_rgb(tokens[5], &quad->color))
		return (false);
	return (true);
}

bool	parse_quad(char **tokens, t_scene *scene)
{
	t_quad	*quad;
	t_list	*node;

	quad = ft_calloc(1, sizeof(t_quad));
	if (!quad)
		return (put_error("Memory allocation failed"));
	if (!check_split_length(tokens, 6))
		return (free(quad), put_error("Invalid quad definition"));
	if (!parse_quad_args(tokens, quad))
		return (free(quad), false);
	node = ft_lstnew(quad);
	if (!node)
		return (free(quad), put_error("Memory allocation failed"));
	ft_lstadd_back(&scene->quads, node);
	return (true);
}