/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narek <narek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 18:06:52 by maghumya          #+#    #+#             */
/*   Updated: 2026/05/01 15:19:46 by narek            ###   ########.fr       */
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

static bool parse_cone_args(char **tokens, t_cone* cone)
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
		return (free(cone), put_error("Invalid cone defention"));
	if (!parse_cone_args(tokens, cone))
		return (free(cone), false);

	node = ft_lstnew(cone);
	if (!node)
		return (free(cone), put_error("Memory allocation failed"));
	ft_lstadd_back(&scene->cones, node);
	return (true);
}


