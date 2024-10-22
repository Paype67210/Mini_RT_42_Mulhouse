/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_resol.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:14:04 by pdeson            #+#    #+#             */
/*   Updated: 2024/10/18 08:37:00 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/mini_rt.h"

void	ft_getscreensize(void)
{
	int32_t		maxwidth;
	int32_t		maxheight;
	mlx_t		*tmp;

	if (g_image->vp->ratio == -1)
		g_image->vp->ratio = 16.0 / 9;
	tmp = mlx_init(10, 10, "miniRT", False);
	mlx_get_monitor_size(0, &maxwidth, &maxheight);
	mlx_terminate(tmp);
	if (maxwidth && (g_image->img_width > maxwidth / 2 || \
		g_image->img_height > maxheight / 2 || g_image->img_width < 42 || \
		g_image->img_height < 42))
	{
		g_image->img_width = maxwidth / 2;
		g_image->img_height = g_image->img_width / g_image->vp->ratio;
	}
	if (g_image->vp_height == 0 || g_image->vp_width == 0)
	{
		g_image->vp_height = g_image->img_height;
		g_image->vp_width = g_image->img_width;
	}
	return ;
}

static int	ft_save_resol(char **grid)
{
	g_image->vp_width = ft_atoi(grid[1]);
	g_image->vp_height = ft_atoi(grid[2]);
	if (ft_strcmp(ft_itoa(g_image->vp_width), grid[1]) || \
		ft_strcmp(ft_itoa(g_image->vp_height), grid[2]))
	{
		printf("Erreur de conversion ATOI\n");
		return (EXIT_FAILURE);
	}
	ft_fprintf(2, "Resolution .rt: width = %i\theight = %i\n", \
		g_image->vp_width, g_image->vp_height);
	g_image->vp->ratio = (double)g_image->vp_width / g_image->vp_height;
	return (EXIT_SUCCESS);
}

int	ft_extract_resol(char *line)
{
	char	**buffer;

	buffer = ft_spsplit(line, 0);
	if (!buffer || ft_split_count(buffer) != 3)
		return (ft_fprintf(2, "Parsing Err: extract resol: Parameters\n"));
	if (buffer[0] && !ft_strcmp(buffer[0], "R"))
	{
		if (ft_save_resol(buffer))
			return (EXIT_FAILURE);
	}
	else
		return (ft_fprintf(2, "Parsing Err: saving Resol failed!\n"));
	ft_fprintf(2, "Resolution definition OK!\n");
	return (EXIT_SUCCESS);
}
