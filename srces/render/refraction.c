/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:44:11 by pdeson            #+#    #+#             */
/*   Updated: 2024/10/18 08:32:01 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/mini_rt.h"

void	refraction(t_scene *scene, t_ray *ray, t_color color)
{
	int		maxiter;
	double	ratio;

	ratio = (1.0 / (ray->depth + 1));
	if (ratio <= 0.1)
		return ;
	if (scene->calc)
		maxiter = 3;
	else
		maxiter = 1;
	(void)scene;
	if (!(color.r == 0 && color.g == 0 && color.b == 0 && color.a == 255))
	{
		ray->direct = vec3_normalize(vec3_reflect(ray->direct, ray->perp));
		ray->color = ft_color_blend(ratio, ray->color, color);
	}
	ray->color.r = fmin(fmax(ray->color.r, 0), 255);
	ray->color.g = fmin(fmax(ray->color.g, 0), 255);
	ray->color.b = fmin(fmax(ray->color.b, 0), 255);
	ray->depth++;
	if (ray->depth == maxiter)
		return ;
	ft_find_pixel_color(scene, ray);
	return ;
}
