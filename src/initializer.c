/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narek <narek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 19:15:26 by maghumya          #+#    #+#             */
/*   Updated: 2026/05/01 15:00:42 by narek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

bool	initialize_scene(char *filename, t_scene *scene)
{
	scene->ambient_intensity = 0.0;
	scene->ambient_light = (t_rgb){0, 0, 0};
	scene->camera = NULL;
	scene->lights = NULL;
	scene->spheres = NULL;
	scene->planes = NULL;
	scene->cylinders = NULL;
	scene->cones = NULL;
	if (!read_file(filename, scene))
		return (false);
	return (true);
}

bool	clean_scene(t_scene *scene)
{
	ft_lstclear(&scene->lights, free);
	ft_lstclear(&scene->spheres, free);
	ft_lstclear(&scene->planes, free);
	ft_lstclear(&scene->cylinders, free);
	ft_lstclear(&scene->cones, free);
	if (scene->camera)
		free(scene->camera);
	return (true);
}
