/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 22:15:01 by philippe          #+#    #+#             */
/*   Updated: 2024/09/16 10:33:32 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/mini_rt.h"

t_vec3	vec3_create(double x, double y, double z)
{
	t_vec3	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

/* Additionne les coordonnees de V1 & V2 */
t_vec3	vec3_add(t_vec3 v1, t_vec3 v2)
{
	return (vec3_create(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
}

/* Soustrait V2 a V1 */
t_vec3	vec3_sub(t_vec3 v1, t_vec3 v2)
{
	return (vec3_create(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
}

/* Multiplie V1 par V2 */
t_vec3	vec3_mul(t_vec3 v1, t_vec3 v2)
{
	return (vec3_create(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z));
}

/* Divise V1 par V2 sauf si V2 = 0 sur un axe */
t_vec3	vec3_div(t_vec3 v1, t_vec3 v2)
{
	if (!v2.x || !v2.y || !v2.z)
	{
		ft_fprintf(2, "Error: vec3_div: division by zero\n");
		return (v1);
	}
	return (vec3_create(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z));
}
