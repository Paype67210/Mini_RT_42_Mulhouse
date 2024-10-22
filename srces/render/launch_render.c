/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:37:10 by pdeson            #+#    #+#             */
/*   Updated: 2024/10/16 13:57:16 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/mini_rt.h"

int	ft_launch_render(t_scene *scene)
{
	int		maxiter;

	if (MAX_ITER > 1000)
		maxiter = 1000;
	else
		maxiter = MAX_ITER;
	th_launch_threads(scene);
	ft_fprintf(1, "Complete Rendering is launched for %i iterations...\n", \
		maxiter);
	return (EXIT_SUCCESS);
}
