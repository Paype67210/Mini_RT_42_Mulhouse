/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 22:15:01 by philippe          #+#    #+#             */
/*   Updated: 2024/10/16 12:28:30 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/mini_rt.h"

t_vec3	vec3_scale(t_vec3 v, double scale)
{
	return (vec3_create(v.x * scale, v.y * scale, v.z * scale));
}

/*
Calcul le produit scalaire des 2 vecteurs V1 & V2
si vec3_dot = 0, les vecteurs sont perpendiculaires
si vec3_dot est negatif, les 2 vecteurs sont oposes, sinon ils vont dans 
une direction similaire
*/
double	vec3_dot(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

/*
Calcul du produit vectoriel entre V1 & V2
le vecteur de sortie est perpendiculaire aux deux autres
*/
t_vec3	vec3_cross(t_vec3 v1, t_vec3 v2)
{
	return (vec3_create(v1.y * v2.z - v1.z * v2.y, \
		v1.z * v2.x - v1.x * v2.z, \
		v1.x * v2.y - v1.y * v2.x));
}

double	vec3_length(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

/*
Definition du vecteur unitaire de v
*/

t_vec3	vec3_normalize(t_vec3 v)
{
	if (!v.x && !v.y && !v.z)
	{
		ft_fprintf(2, "Error: vec3_normalize: division by zero\n");
		return (v);
	}
	if (vec3_length(v) == 0)
		ft_fprintf(2, "Error: vec3_normalize: division by zero\n");
	return (vec3_scale(v, 1.0 / vec3_length(v)));
}
