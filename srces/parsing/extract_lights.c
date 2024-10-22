/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_lights.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:14:04 by pdeson            #+#    #+#             */
/*   Updated: 2024/10/15 13:09:12 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/mini_rt.h"

static int	ft_save_light(t_scene *scene, char **grid)
{
	t_list	*node;
	t_obj	*obj;
	char	*endptrfl;

	obj = ft_run_malloc(1, sizeof(t_obj));
	node = ft_run_malloc(1, sizeof(t_list));
	if (!obj || !node)
		return (ft_fprintf(2, "Malloc failed: ft_save_light\n"));
	if (ft_parse_vec3(grid[1], &(obj->coordos)))
		return (ft_fprintf(1, "Parsing Err: No valid light position.\n"));
	obj->ratio = ft_strtod(grid[2], &endptrfl);
	if (endptrfl == grid[2] || obj->ratio < 0.0 || \
		obj->ratio > 1.0)
		return (ft_fprintf(2, "Parsing Err: No valid light ratio.\n"));
	if (ft_parse_color(&(obj->color), grid[3]))
		return (ft_fprintf(2, "Parsing Err: Colors in [0-255]\n"));
	obj->color = ft_color_scale(obj->ratio, obj->color);
	node->content = obj;
	ft_lstadd_back(&scene->lights, node);
	return (EXIT_SUCCESS);
}

int	ft_extract_lights(t_scene *scene, char *line)
{
	char		**buffer;

	buffer = ft_spsplit(line, 0);
	if (!buffer || ft_split_count(buffer) != 4)
		return (ft_fprintf(2, "Parsing Err: extract Light: Parameters\n"));
	if (buffer[0] && !ft_strcmp(buffer[0], "L"))
	{
		if (ft_save_light(scene, buffer))
			return (EXIT_FAILURE);
	}
	else
		return (ft_fprintf(2, "Parsing Err: saving Light failed!\n"));
	return (EXIT_SUCCESS);
}
