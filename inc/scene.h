/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narek <narek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 15:30:00 by maghumya          #+#    #+#             */
/*   Updated: 2026/05/01 14:59:31 by narek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "vec3d.h"
# include "window.h"

typedef struct s_list		t_list;
typedef struct s_hit_record	t_hit_record;

typedef struct s_viewport
{
	t_vec3					center;
	t_vec3					upper_left;
	t_vec3					horizontal;
	t_vec3					vertical;
	double					height;
	double					width;
	double					focal_length;
}							t_viewport;

typedef struct s_scene
{
	t_rgb					ambient_light;
	double					ambient_intensity;
	t_camera				*camera;
	t_list					*lights;
	t_list					*spheres;
	t_list					*planes;
	t_list					*cylinders;
	t_list					*cones;
	t_list 					*boxes;
	t_viewport				viewport;
}							t_scene;

typedef struct s_data
{
	t_mlx					mlx;
	t_scene					scene;
}							t_data;

typedef struct s_box
{
	t_vec3 center;
	t_vec3 size;
	t_rgb color;
} t_box;


bool						initialize_scene(char *filename, t_scene *scene);
bool						clean_scene(t_scene *scene);
t_viewport					setup_viewport(t_camera *camera, int image_width,
								int image_height);
t_ray						generate_ray(t_data *data, int x, int y);
t_rgb						calculate_light(t_scene *scene,
								t_hit_record *record);
void						tracer_loop(t_data *data);

#endif
