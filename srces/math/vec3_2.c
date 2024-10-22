/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 22:15:01 by philippe          #+#    #+#             */
/*   Updated: 2024/08/26 10:33:02 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/mini_rt.h"

/*
Calcule le vecteur reflechi de v par rapport au vecteur normal n
*/

t_vec3	vec3_reflect(t_vec3 v, t_vec3 n)
{
	return (vec3_sub(v, vec3_scale(n, 2 * vec3_dot(v, n))));
}

/*
renvoie un vecteur constitue des valeurs minimales sur chacun des axes de V1 & V2
utile pour le calcul d'intersection de volumes ?
*/

t_vec3	vec3_min(t_vec3 v1, t_vec3 v2)
{
	return (vec3_create(fmin(v1.x, v2.x), fmin(v1.y, v2.y), fmin(v1.z, v2.z)));
}

/*
renvoie un vecteur constitue des valeurs maximales sur chacun des axes de V1 & V2
utile pour le calcul d'intersection de volumes ?
*/

t_vec3	vec3_max(t_vec3 v1, t_vec3 v2)
{
	return (vec3_create(fmax(v1.x, v2.x), fmax(v1.y, v2.y), fmax(v1.z, v2.z)));
}

t_vec3	vec3_zero(void)
{
	return (vec3_create(0, 0, 0));
}

int	ft_parse_vec3(const char *str, t_vec3 *result)
{
	char	*endptrd;
	char	**split;

	split = ft_split(str, ',');
	if (!split)
		return (EXIT_FAILURE);
	if (ft_split_count(split) != 3)
		return (EXIT_FAILURE);
	else
	{
		result->x = ft_strtod(split[0], &endptrd);
		if (!(*endptrd))
			result->y = ft_strtod(split[1], &endptrd);
		if (!(*endptrd))
			result->z = ft_strtod(split[2], &endptrd);
		if (!(*endptrd))
			return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
