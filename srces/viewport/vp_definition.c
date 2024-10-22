/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vp_definition.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:32:07 by pdeson            #+#    #+#             */
/*   Updated: 2024/10/18 08:35:51 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/mini_rt.h"

static	t_vec3	define_up(t_vec3 vector)
{
	if (fabs(vector.y) > 0.99)
		return ((t_vec3){0, 0, 1});
	else
		return ((t_vec3){0, 1, 0});
}

int	ft_deltas(t_scene *scene)
{
	t_vec3	up_global;
	t_vec3	upper_left;

	up_global = define_up(scene->camera->vect_norm);
	g_image->vp->img_center = vec3_add(scene->camera->coordos, \
		vec3_scale(scene->camera->vect_norm, g_image->vp->focal));
	g_image->vp->vp_u = vec3_scale(vec3_normalize(vec3_cross(up_global, \
		scene->camera->vect_norm)), g_image->vp_width);
	g_image->vp->vp_v = vec3_scale(vec3_normalize(vec3_cross(g_image->vp->vp_u, \
		scene->camera->vect_norm)), g_image->vp_height);
	if (!scene->ok)
	{
		g_image->vp->delta_u = vec3_scale(g_image->vp->vp_u, \
			1 / (double)g_image->img_width);
		g_image->vp->delta_v = vec3_scale(g_image->vp->vp_v, \
			1 / (double)g_image->img_height);
		scene->ok = true;
	}
	upper_left = vec3_sub(g_image->vp->img_center, \
		vec3_scale(g_image->vp->vp_u, 0.5));
	upper_left = vec3_sub(upper_left, vec3_scale(g_image->vp->vp_v, 0.5));
	g_image->vp->pixel00 = vec3_add(upper_left, \
		vec3_scale(vec3_add(g_image->vp->delta_u, g_image->vp->delta_v), 0.5));
	return (EXIT_SUCCESS);
}

int	ft_viewport(t_scene *scene)
{
	g_image->img_width = 2 * (g_image->vp_width) * \
		tan(scene->camera->fov / 2);
	g_image->img_height = g_image->vp_width * \
		((double)(g_image->vp_height / g_image->vp_height));
	ft_getscreensize();
	g_image->vp->scale = tan(scene->camera->fov * 0.5 * M_PI / 180.0);
	g_image->vp->focal = (g_image->img_width * 0.5) / g_image->vp->scale;
	ft_deltas(scene);
	ft_launch_vp(scene);
	return (EXIT_SUCCESS);
}
