/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_perp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:43:41 by pdeson            #+#    #+#             */
/*   Updated: 2024/09/25 14:43:50 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/mini_rt.h"

t_vec3	cylinder_normal(t_obj *tmp, t_ray *ray)
{
	double	proj_length;
	t_vec3	pint;
	t_vec3	proj;

	pint = vec3_sub(ray->origin, tmp->coordos);
	proj_length = vec3_dot(pint, tmp->vector) / \
		vec3_dot(tmp->vector, tmp->vector);
	proj = vec3_scale(tmp->vector, proj_length);
	return (vec3_scale(vec3_sub(pint, proj), -1));
}

t_vec3	cone_normal(t_obj *tmp, t_ray *ray)
{
	t_vec3	cone_apex;
	t_vec3	relative_inter;
	double	proj;
	t_vec3	axis;

	cone_apex = vec3_sub(tmp->coordos, \
		vec3_scale(tmp->vector, tmp->height));
	relative_inter = vec3_sub(ray->origin, cone_apex);
	proj = vec3_dot(relative_inter, tmp->vector);
	axis = vec3_scale(tmp->vector, proj);
	return (vec3_normalize(vec3_sub(relative_inter, axis)));
}
