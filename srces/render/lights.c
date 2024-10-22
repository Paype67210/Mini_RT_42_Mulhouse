/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:43:09 by pdeson            #+#    #+#             */
/*   Updated: 2024/10/01 11:11:23 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/mini_rt.h"

int	is_in_shadow(t_scene *scene, t_ray *ray, t_obj *tmp)
{
	t_list	*obj;

	obj = ft_lstfirst(scene->objects);
	while (obj)
	{
		if (obj->content != tmp)
		{
			if (which_obj(ray, obj) > 0)
				return (1);
		}
		obj = obj->next;
	}
	return (0);
}

t_color	light_hit(t_scene *scene, t_list *lights, t_ray *hit, t_obj *tmp)
{
	t_obj	*buffer;
	t_color	color;
	t_vec3	li;
	double	impact;
	t_ray	shadow_ray;

	color = tmp->color;
	while (lights)
	{
		buffer = lights->content;
		li = vec3_normalize(vec3_sub(hit->origin, buffer->coordos));
		impact = vec3_dot(li, vec3_normalize(hit->perp));
		shadow_ray.origin = hit->origin;
		shadow_ray.direct = vec3_sub(buffer->coordos, hit->origin);
		if (is_in_shadow(scene, &shadow_ray, tmp) == 1 && impact > 0)
			impact *= -1;
		impact *= buffer->ratio;
		color = ft_color_blend(impact, color, buffer->color);
		lights = lights->next;
	}
	return (color);
}
