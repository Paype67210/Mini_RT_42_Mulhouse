/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_pl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:05:44 by pdeson            #+#    #+#             */
/*   Updated: 2024/10/15 13:09:20 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/mini_rt.h"

/* PLANE -> NODE.TYPE = 2 */

static int	ft_save_pl(t_scene *scene, char **grid)
{
	t_list	*node;
	t_obj	*obj;

	obj = ft_run_malloc(1, sizeof(t_obj));
	node = ft_run_malloc(1, sizeof(t_list));
	if (!obj || !node)
		return (ft_fprintf(2, "Malloc failed: ft_save_pl\n"));
	if (ft_parse_vec3(grid[1], &(obj->coordos)))
		return (ft_fprintf(1, "Parsing Err: No valid Plane position.\n"));
	if (ft_parse_vec3(grid[2], &(obj->vector)) || \
		vec3_length(obj->vector) > sqrt(3))
		return (ft_fprintf(2, "Parsing Err: No valid Plane orientation.\n"));
	if (ft_parse_color(&(obj->color), grid[3]))
		return (ft_fprintf(2, "Parsing Err: Colors in [0-255]\n"));
	node->type = 2;
	node->content = obj;
	ft_lstadd_back(&scene->objects, node);
	return (EXIT_SUCCESS);
}

int	ft_extract_pl(t_scene *scene, char *line)
{
	char		**buffer;

	buffer = ft_spsplit(line, 0);
	if (!buffer || ft_split_count(buffer) != 4)
		return (ft_fprintf(2, "Parsing Err: extract Plane: Parameters\n"));
	if (buffer[0] && !ft_strcmp(buffer[0], "pl"))
	{
		if (ft_save_pl(scene, buffer))
			return (EXIT_FAILURE);
	}
	else
		return (ft_fprintf(2, "Parsing Err: saving Plane failed!\n"));
	return (EXIT_SUCCESS);
}
