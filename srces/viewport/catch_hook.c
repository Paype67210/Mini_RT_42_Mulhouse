/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:45:02 by pdeson            #+#    #+#             */
/*   Updated: 2024/10/16 12:32:16 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/mini_rt.h"

void	ft_move_obj(t_scene *scene, t_obj *obj, int x, int y)
{
	t_vec3	new_dir;
	t_vec3	pxlxy;
	t_vec3	buffer;
	double	dist;

	dist = vec3_length(vec3_sub(obj->coordos, scene->camera->coordos));
	printf("dist: %.1f\n", dist);
	pxlxy = vec3_add(g_image->vp->pixel00, vec3_scale(g_image->vp->delta_u, x));
	pxlxy = vec3_add(pxlxy, vec3_scale(g_image->vp->delta_v, y));
	new_dir = vec3_normalize(vec3_sub(pxlxy, scene->camera->coordos));
	buffer = vec3_add(scene->camera->coordos, vec3_scale(new_dir, dist));
	obj->coordos = buffer;
	printf("New Coordos: %.1f, %.1f, %.1f\n", \
		obj->coordos.x, obj->coordos.y, obj->coordos.z);
}

int	ft_mouse2(void *scene)
{
	int32_t		mouse_x;
	int32_t		mouse_y;
	t_obj		*buffer;
	t_ray		*ray;

	ray = ft_run_malloc(1, sizeof(t_ray));
	mlx_get_mouse_pos(g_image->mlxptr, &mouse_x, &mouse_y);
	init_ray(scene, ray, mouse_x, mouse_y);
	buffer = ft_find_pixel_color(scene, ray);
	if (buffer)
	{
		printf("Obj saisi.\n");
		printf("Coordos: [%.1f, %.1f, %.1f]\n", \
			buffer->coordos.x, buffer->coordos.y, buffer->coordos.z);
		scene_cont(scene)->trashcoordos = &buffer->coordos;
		scene_cont(scene)->trashvector = &buffer->vector;
		return (1);
	}
	else
		return (-1);
}

void	ft_hook2(void *scene)
{
	ft_deltas(scene);
	ft_render(scene);
	mlx_image_to_window(g_image->mlxptr, g_image->winptr, 0, 0);
	return ;
}

void	ft_mouse(enum mouse_key key, enum action action, \
			enum modifier_key mods, void *scene)
{
	static int	catch;

	if (scene_cont(scene)->calc)
		return ;
	(void)mods;
	if (key == 0 && action == 1)
	{
		if (catch != 1)
			catch = ft_mouse2(scene);
		else
		{
			scene_cont(scene)->trashcoordos = \
				&scene_cont(scene)->camera->coordos;
			scene_cont(scene)->trashvector = \
				&scene_cont(scene)->camera->vect_norm;
			printf("Obj laché.\n");
			catch = -1;
		}
	}
	return ;
}
