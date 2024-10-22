/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_amb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:14:04 by pdeson            #+#    #+#             */
/*   Updated: 2024/09/16 14:26:34 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/mini_rt.h"

static int	ft_save_amb(t_scene *scene, char **grid)
{
	char	*endptrfl;

	scene->ambiant->ratio = ft_strtod(grid[1], &endptrfl);
	if (endptrfl == grid[1] || scene->ambiant->ratio < 0.0 || \
		scene->ambiant->ratio > 1.0)
		return (ft_fprintf(2, "Parsing Err: No valid conversion performed!\n"));
	if (ft_parse_color(&(scene->ambiant->color), grid[2]))
		return (ft_fprintf(2, "Parsing Err: Colors in [0-255]\n"));
	scene->ambiant->color = ft_color_scale(scene->ambiant->ratio, \
		scene->ambiant->color);
	return (EXIT_SUCCESS);
}

int	ft_extract_amb(t_scene *scene, char *line)
{
	char	**buffer;

	if (scene->ambiant->exist)
		return (ft_msg("Parsing Err: ", "Too many A id.", NULL, 1));
	buffer = ft_spsplit(line, 0);
	if (!buffer || ft_split_count(buffer) != 3)
		return (ft_fprintf(2, "Parsing Err: extract amb: Parameters\n"));
	if (buffer[0] && !ft_strcmp(buffer[0], "A"))
	{
		if (ft_save_amb(scene, buffer))
			return (EXIT_FAILURE);
	}
	else
		return (ft_fprintf(2, "Parsing Err: saving Amb failed!\n"));
	scene->ambiant->exist = true;
	ft_fprintf(2, "Ambiant Light definition OK!\n");
	return (EXIT_SUCCESS);
}
