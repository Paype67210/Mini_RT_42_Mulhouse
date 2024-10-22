/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 11:17:47 by pdeson            #+#    #+#             */
/*   Updated: 2024/10/16 13:07:50 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/mini_rt.h"

void	which_obj_perp(t_ray *ray, t_obj *tmp, double t)
{
	if (tmp->type == 1)
	{
		ray->origin = vec3_add(ray->origin, vec3_scale(ray->direct, t));
		ray->perp = vec3_sub(tmp->coordos, ray->origin);
	}
	else if (tmp->type == 2)
	{
		ray->origin = vec3_add(ray->origin, vec3_scale(ray->direct, t));
		ray->perp = tmp->vector;
	}
	else if (tmp->type == 3)
	{
		ray->origin = vec3_add(ray->origin, vec3_scale(ray->direct, t));
		ray->perp = cylinder_normal(tmp, ray);
	}
	else if (tmp->type == 4)
	{
		ray->origin = vec3_add(ray->origin, vec3_scale(ray->direct, t));
		ray->perp = cone_normal(tmp, ray);
	}
	return ;
}

double	which_obj(t_ray *ray, t_list *obj)
{
	if (obj->type == 1)
		return (sp_intersection(obj->content, ray));
	else if (obj->type == 2)
		return (pl_intersection(obj->content, ray));
	else if (obj->type == 3)
		return (cy_intersection(obj->content, ray));
	else if (obj->type == 4)
		return (co_intersection(obj->content, ray));
	return (-1);
}

static t_obj	*ft_obj_tmp(t_list *obj, t_ray *ray, double *t)
{
	t_obj	*tmp;
	double	buffer;

	while (obj)
	{
		buffer = which_obj(ray, obj);
		if (buffer >= 0)
		{
			if (*t == -1 || *t > buffer)
			{
				*t = buffer;
				tmp = obj_cont(obj);
				tmp->type = obj->type;
			}
		}
		obj = obj->next;
	}
	return (tmp);
}

t_obj	*ft_find_pixel_color(t_scene *scene, t_ray *ray)
{
	t_list	*obj;
	t_obj	*tmp;
	double	t;

	tmp = NULL;
	obj = ft_lstfirst(scene->objects);
	t = -1;
	tmp = ft_obj_tmp(obj, ray, &t);
	if (t > 0)
	{
		which_obj_perp(ray, tmp, t);
		refraction(scene, ray, light_hit(scene, \
			ft_lstfirst(scene->lights), ray, tmp));
	}
	else if (ray->depth == 0)
		ray->color = scene->ambiant->color;
	return (tmp);
}
