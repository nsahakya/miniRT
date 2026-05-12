/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narek <narek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 15:30:00 by maghumya          #+#    #+#             */
/*   Updated: 2026/05/01 15:01:27 by narek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../libft/libft.h"
# include "scene.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

typedef bool	(*t_parse_fn)(char **, t_scene *);

/* Parsing functions */
bool			read_file(char *filename, t_scene *scene);
bool			parse_ambient_light(char **tokens, t_scene *scene);
bool			parse_camera(char **tokens, t_scene *scene);
bool			parse_light(char **tokens, t_scene *scene);
bool			parse_sphere(char **tokens, t_scene *scene);
bool			parse_plane(char **tokens, t_scene *scene);
bool			parse_cylinder(char **tokens, t_scene *scene);
bool			parse_box(char **tokens, t_scene *scene);
bool			parse_cone(char **tokens, t_scene *scene);
bool			parse_vec3(char *str, t_vec3 *vec);
bool			parse_rgb(char *str, t_rgb *color);

/* Validation functions */
bool			check_file_extension(char *filename);
bool			check_double(const char *str);
bool			check_integer(const char *str);
bool			check_rgb_values(int r, int g, int b);
bool			check_split_length(char **tokens, int expected_length);
bool			check_arg_format(char **tokens, int expected_length,
					bool (*check_func)(const char *));
bool			check_ranged(double value, double min, double max);
bool			check_range_vec3(t_vec3 vec, double min, double max);
bool			put_error(char *message);

#endif
