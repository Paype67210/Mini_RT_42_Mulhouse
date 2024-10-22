/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 11:32:11 by pdeson            #+#    #+#             */
/*   Updated: 2024/10/16 10:05:24 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/mini_rt.h"

int	ft_exit(t_scene *scene, int status)
{
	if (scene->save)
	{
		if (save_bmp(scene->file))
			return (ft_msg("Error: ", "Saving_file: ", "failed", EXIT_FAILURE));
	}
	if (!g_image)
		status = 2;
	if (g_image->winptr)
	{
		status = 3;
		mlx_delete_image(g_image->mlxptr, g_image->winptr);
		mlx_terminate(g_image->mlxptr);
	}
	ft_fprintf(2, "FERMETURE MINI_RT\n");
	close(STDERR_FILENO);
	ft_run_malloc(4);
	return (status);
}

void	ft_handle_signal(int signal)
{
	if (signal == SIGTERM || signal == SIGINT)
	{
		if (g_image->winptr)
		{
			mlx_delete_image(g_image->mlxptr, g_image->winptr);
			mlx_terminate(g_image->mlxptr);
		}
		ft_fprintf(2, "FERMETURE MINI_RT\n");
		close(STDERR_FILENO);
		ft_run_malloc(4);
		exit (0);
	}
}
