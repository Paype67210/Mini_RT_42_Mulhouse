/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:12:09 by pdeson            #+#    #+#             */
/*   Updated: 2024/10/07 11:02:48 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/mini_rt.h"

double	ft_vector_turn(double vector, double delta)
{
	if (vector + delta > 1)
		return (1);
	else if (vector + delta < -1)
		return (-1);
	return (delta + vector);
}

void	ft_cam_move_bf(t_scene *scene, int delta)
{
	t_vec3	buff_delta_p;
	t_vec3	buffer;

	buff_delta_p = scene->camera->vect_norm;
	buffer = vec3_add(scene->camera->coordos, vec3_scale(buff_delta_p, delta));
	scene->camera->coordos = buffer;
}
