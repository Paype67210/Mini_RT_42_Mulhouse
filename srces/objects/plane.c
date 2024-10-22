/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:04:43 by pdeson            #+#    #+#             */
/*   Updated: 2024/09/17 12:05:58 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/mini_rt.h"

double	pl_intersection(t_obj *obj, t_ray *ray)
{
	t_vec3	origin_to_plane;
	double	denominator;
	double	t;

	origin_to_plane = vec3_sub(obj->coordos, ray->origin);
	denominator = vec3_dot(obj->vector, ray->direct);
	if (fabs(denominator) < 1e-6)
		return (-1);
	t = vec3_dot(obj->vector, origin_to_plane) / denominator;
	if (t < 0)
		return (-1);
	return (t);
}
