/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:48:52 by pdeson            #+#    #+#             */
/*   Updated: 2024/10/18 10:23:58 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/mini_rt.h"

static t_vec3	co_calc_abc(t_obj *obj, t_ray *ray)
{
	t_vec3	buffer;
	t_vec3	oc;
	t_vec3	d_cross_v;
	t_vec3	oc_cross_v;
	double	r;

	r = calc_r(obj);
	oc = vec3_sub(ray->origin, obj->coordos);
	d_cross_v = vec3_cross(ray->direct, obj->vector);
	oc_cross_v = vec3_cross(oc, obj->vector);
	buffer.x = vec3_dot(d_cross_v, d_cross_v) - \
		(r / obj->height) * (r / obj->height) * (vec3_dot(ray->direct, \
		obj->vector) * vec3_dot(ray->direct, obj->vector));
	buffer.y = 2 * (vec3_dot(d_cross_v, oc_cross_v) - \
		(r / obj->height) * (r / obj->height) * vec3_dot(ray->direct, \
		obj->vector) * vec3_dot(oc, obj->vector));
	buffer.z = vec3_dot(oc_cross_v, oc_cross_v) - \
		((r / obj->height) * (r / obj->height)) * (vec3_dot(oc, obj->vector) * \
		vec3_dot(oc, obj->vector));
	return (buffer);
}

double	co_intersection(t_obj *obj, t_ray *ray)
{
	t_vec3	abc;
	double	det;
	double	t;
	double	proj_length;

	abc = co_calc_abc(obj, ray);
	det = abc.y * abc.y - 4 * abc.x * abc.z;
	if (det >= 0)
	{
		t = return_t(abc, det);
		if (t > 0)
		{
			proj_length = vec3_dot(vec3_sub(vec3_add(ray->origin, \
				vec3_scale(ray->direct, t)), obj->coordos), \
				vec3_normalize(obj->vector));
			if (proj_length >= 0 && proj_length <= calc_height(obj))
				return (t);
		}
	}
	return (co_base(ray, obj, (calc_r(obj) / 2)));
}
