/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 09:46:42 by pdeson            #+#    #+#             */
/*   Updated: 2024/09/24 09:54:51 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/mini_rt.h"

int	scene_light_weights(t_list *lights)
{
	t_list	*iter;
	double	weight_sum;

	if (!lights)
		return (EXIT_FAILURE);
	weight_sum = 0;
	iter = ft_lstfirst(lights);
	while (iter)
	{
		weight_sum += obj_cont(iter)->ratio;
		iter = iter->next;
	}
	if (weight_sum <= 0)
		return (EXIT_FAILURE);
	iter = ft_lstfirst(lights);
	while (iter)
	{
		obj_cont(iter)->ratio /= weight_sum;
		iter = iter->next;
	}
	return (EXIT_SUCCESS);
}
