/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narek <narek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 15:19:45 by maghumya          #+#    #+#             */
/*   Updated: 2026/05/04 12:32:23 by narek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

static t_parse_fn	get_parser(char *identifier)
{
	if (ft_strcmp(identifier, "A") == 0)
		return (parse_ambient_light);
	else if (ft_strcmp(identifier, "C") == 0)
		return (parse_camera);
	else if (ft_strcmp(identifier, "L") == 0)
		return (parse_light);
	else if (ft_strcmp(identifier, "sp") == 0)
		return (parse_sphere);
	else if (ft_strcmp(identifier, "pl") == 0)
		return (parse_plane);
	else if (ft_strcmp(identifier, "cy") == 0)
		return (parse_cylinder);
	else if (ft_strcmp(identifier, "cn") == 0)
		return (parse_cone);
	else if (ft_strcmp(identifier, "bx") == 0)
		return (parse_box);
	else if (ft_strcmp(identifier, "tr") == 0)
		return (parse_triangle);
	else if (ft_strcmp(identifier, "di") == 0)
		return (parse_disc);	
	else if (ft_strcmp(identifier, "qd") == 0)
		return (parse_quad);
	return (NULL);
	
}

static char	*check_trim(char *line)
{
	char	*trimmed_line;

	trimmed_line = ft_strtrim(line, " \t\n");
	if (trimmed_line[0] == '\0' || trimmed_line[0] == '#')
	{
		free(trimmed_line);
		return (NULL);
	}
	return (trimmed_line);
}

static bool	parse_line(char *line, t_scene *scene)
{
	char		**line_tokens;
	t_parse_fn	parser;
	bool		result;
	char		*trimmed_line;

	trimmed_line = check_trim(line);
	if (!trimmed_line)
		return (true);
	line_tokens = ft_split(trimmed_line, ' ');
	free(trimmed_line);
	if (!line_tokens || !line_tokens[0])
	{
		ft_free_array((void ***)&line_tokens);
		return (put_error("Empty line or invalid format"));
	}
	parser = get_parser(line_tokens[0]);
	if (!parser)
	{
		ft_free_array((void ***)&line_tokens);
		return (put_error("Unknown identifier"));
	}
	result = parser(line_tokens, scene);
	ft_free_array((void ***)&line_tokens);
	return (result);
}

bool	read_file(char *filename, t_scene *scene)
{
	int		fd;
	char	*line;

	if (!check_file_extension(filename))
		return (put_error("File must have .rt extension"));
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (put_error("Error opening file"));
	line = get_next_line(fd);
	while (line)
	{
		if (!parse_line(line, scene))
			return (free(line), close(fd), false);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (!scene->camera)
		return (put_error("Scene must have a camera defined"));
	return (true);
}
