/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 12:36:19 by pdeson            #+#    #+#             */
/*   Updated: 2024/10/18 10:29:57 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/mini_rt.h"

static t_vec3	co_calc_btd(t_ray *ray, t_obj *obj, t_vec3 top_center)
{
	t_vec3	buffer;

	buffer.z = vec3_dot(ray->direct, obj->vector);
	buffer.x = vec3_dot(vec3_sub(obj->coordos, ray->origin), \
			obj->vector) / buffer.z;
	buffer.y = vec3_dot(vec3_sub(top_center, ray->origin), \
		obj->vector) / buffer.z;
	return (buffer);
}

static t_vec3	co_calc_ptop(t_ray *ray, double top)
{
	t_vec3	buffer;

	buffer = vec3_add(ray->origin, vec3_scale(ray->direct, top));
	return (buffer);
}

static t_vec3	co_calc_topcenter(t_obj *obj)
{
	t_vec3	buffer;
	double	height;

	height = calc_height(obj);
	buffer = vec3_add(obj->coordos, \
		vec3_scale(vec3_normalize(obj->vector), height));
	return (buffer);
}

double	co_base(t_ray *ray, t_obj *obj, double r)
{
	t_vec3	btd;
	t_vec3	top_center;
	t_vec3	p_top;

	top_center = co_calc_topcenter(obj);
	btd = co_calc_btd(ray, obj, top_center);
	if (fabs(btd.z) > 1e-6)
	{
		if (btd.y > 0)
		{
			p_top = co_calc_ptop(ray, btd.y);
			if (vec3_dot(vec3_sub(p_top, top_center), \
				vec3_sub(p_top, top_center)) <= r * r)
				return (btd.y);
		}
	}
	return (-1);
}
