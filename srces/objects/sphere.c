/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:04:00 by pdeson            #+#    #+#             */
/*   Updated: 2024/09/25 15:49:57 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/mini_rt.h"

static double	calc_a(t_vec3	direct)
{
	return ((pow(direct.x, 2) + pow(direct.y, 2) + pow(direct.z, 2)));
}

static double	calc_b(t_ray ray, t_vec3 obj)
{
	return ((2 * (ray.direct.x * (ray.origin.x - obj.x) + ray.direct.y * \
		(ray.origin.y - obj.y) + ray.direct.z * \
		(ray.origin.z - obj.z))));
}

static double	calc_c(t_ray ray, t_obj obj)
{
	double	dist;
	double	ratio;
	double	radius;

	dist = vec3_length(vec3_sub(obj.coordos, g_image->vp->img_center)) + \
		g_image->vp->focal;
	ratio = g_image->vp->focal / dist;
	radius = obj.dt * 0.5 * ratio;
	return ((pow(ray.origin.x - obj.coordos.x, 2) + \
		pow(ray.origin.y - obj.coordos.y, 2) + \
		pow(ray.origin.z - obj.coordos.z, 2) - pow(radius, 2)));
}

double	sp_intersection(t_obj *obj, t_ray *ray)
{
	double	a;
	double	b;
	double	c;
	double	det;

	a = calc_a(ray->direct);
	b = calc_b(*ray, obj->coordos);
	c = calc_c(*ray, *obj);
	det = b * b - 4 * a * c;
	if (det <= 0)
		return (-1);
	if ((-b + sqrt(det)) / (2 * a) < 0)
		return ((-b - sqrt(det)) / (2 * a));
	else if ((-b - sqrt(det)) / (2 * a) < 0)
		return ((-b + sqrt(det)) / (2 * a));
	return (fmin((-b + sqrt(det)) / (2 * a), \
		(-b - sqrt(det)) / (2 * a)));
}
