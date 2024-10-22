/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:48:16 by pdeson            #+#    #+#             */
/*   Updated: 2024/10/18 09:32:22 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/mini_rt.h"

double	calc_height(t_obj *obj)
{
	double	dist;
	double	ratio;
	double	buffer;

	dist = vec3_length(vec3_sub(obj->coordos, g_image->vp->img_center)) + \
		g_image->vp->focal;
	ratio = g_image->vp->focal / dist;
	buffer = obj->height * 0.5 * ratio;
	return (buffer);
}

double	calc_r(t_obj *obj)
{
	double	dist;
	double	ratio;
	double	radius;

	dist = vec3_length(vec3_sub(obj->coordos, g_image->vp->img_center)) + \
		g_image->vp->focal;
	ratio = g_image->vp->focal / dist;
	radius = obj->dt * 0.5 * ratio;
	return (radius);
}

static t_vec3	calc_abc(t_obj *obj, t_ray *ray)
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
	buffer.x = vec3_dot(d_cross_v, d_cross_v);
	buffer.y = 2 * vec3_dot(d_cross_v, oc_cross_v);
	buffer.z = vec3_dot(oc_cross_v, oc_cross_v) - \
		(r * r * vec3_dot(obj->vector, obj->vector));
	return (buffer);
}

double	return_t(t_vec3 abc, double det)
{
	double	t;

	if ((-abc.y + sqrt(det)) / (2 * abc.x) < 0)
		t = ((-abc.y - sqrt(det)) / (2 * abc.x));
	else if ((-abc.y - sqrt(det)) / (2 * abc.x) < 0)
		t = ((-abc.y + sqrt(det)) / (2 * abc.x));
	else
		t = fmin((-abc.y + sqrt(det)) / (2 * abc.x), \
			(-abc.y - sqrt(det)) / (2 * abc.x));
	return (t);
}

double	cy_intersection(t_obj *obj, t_ray *ray)
{
	t_vec3	abc;
	double	det;
	double	t;
	double	proj_length;

	abc = calc_abc(obj, ray);
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
	return (base_and_top(ray, obj, calc_r(obj)));
}
