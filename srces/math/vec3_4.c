/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 10:56:53 by pdeson            #+#    #+#             */
/*   Updated: 2024/08/23 12:39:24 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/mini_rt.h"

t_vec3	vec3_perp(t_vec3 v, t_vec3 p)
{
	t_vec3	perp;

	perp.x = 1;
	if (v.y != 0)
	{
		perp.y = 0;
		perp.z = -(v.x * perp.x) / v.z;
	}
	else if (v.z != 0)
	{
		perp.z = 0;
		perp.y = -(v.x * perp.x) / v.y;
	}
	else
	{
		perp.y = 1;
		perp.z = 0;
	}
	perp.x += p.x;
	perp.y += p.y;
	perp.z += p.z;
	return (perp);
}

double	vec3_dis(t_vec3 p1, t_vec3 p2)
{
	return (sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) + \
		pow(p2.z - p1.z, 2)));
}

int	vec3_cmp(t_vec3 p1, t_vec3 p2)
{
	if (p1.x != p2.x)
		return (1);
	if (p1.y != p2.y)
		return (1);
	if (p1.z != p2.z)
		return (1);
	return (0);
}
