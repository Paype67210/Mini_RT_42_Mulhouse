/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_sp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:06:20 by pdeson            #+#    #+#             */
/*   Updated: 2024/10/15 13:09:30 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/mini_rt.h"

/* SPHERE -> NODE.TYPE = 1 */

static int	ft_save_sp(t_scene *scene, char **grid)
{
	t_list	*node;
	t_obj	*obj;
	char	*endptrfl;

	obj = ft_run_malloc(1, sizeof(t_obj));
	node = ft_run_malloc(1, sizeof(t_list));
	if (!obj || !node)
		return (ft_fprintf(2, "Malloc failed: ft_save_sp\n"));
	if (ft_parse_vec3(grid[1], &(obj->coordos)))
		return (ft_fprintf(1, "Parsing Err: No valid sphere position.\n"));
	obj->dt = ft_strtod(grid[2], &endptrfl);
	if (endptrfl == grid[2] || obj->dt <= 0.0)
		return (ft_fprintf(2, "Parsing Err: No valid sphere diam.\n"));
	if (ft_parse_color(&(obj->color), grid[3]))
		return (ft_fprintf(2, "Parsing Err: Colors in [0-255]\n"));
	node->type = 1;
	node->content = obj;
	ft_lstadd_back(&scene->objects, node);
	return (EXIT_SUCCESS);
}

int	ft_extract_sp(t_scene *scene, char *line)
{
	char		**buffer;

	buffer = ft_spsplit(line, 0);
	if (!buffer || ft_split_count(buffer) != 4)
		return (ft_fprintf(2, "Parsing Err: extract Sphere: Parameters\n"));
	if (buffer[0] && !ft_strcmp(buffer[0], "sp"))
	{
		if (ft_save_sp(scene, buffer))
			return (EXIT_FAILURE);
	}
	else
		return (ft_fprintf(2, "Parsing Err: saving Sphere failed!\n"));
	return (EXIT_SUCCESS);
}
