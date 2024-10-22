/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_co.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:13:52 by pdeson            #+#    #+#             */
/*   Updated: 2024/10/16 13:14:03 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/mini_rt.h"

/* CYLENDER -> NODE.TYPE = 3 */

static int	ft_save_co(t_scene *scene, char **grid)
{
	t_list	*node;
	t_obj	*obj;
	char	*endptrfl;

	obj = ft_run_malloc(1, sizeof(t_obj));
	node = ft_run_malloc(1, sizeof(t_list));
	if (ft_parse_vec3(grid[1], &(obj->coordos)))
		return (ft_fprintf(1, "Parsing Err: No valid Cone position.\n"));
	if (ft_parse_vec3(grid[2], &(obj->vector)) || \
		vec3_length(obj->vector) > sqrt(3))
		return (ft_fprintf(2, "Parsing Err: No valid Cone orientation.\n"));
	obj->dt = ft_strtod(grid[3], &endptrfl);
	if (endptrfl == grid[3] || obj->dt <= 0.0)
		return (ft_fprintf(2, "Parsing Err: No valid Cone diam.\n"));
	obj->height = ft_strtod(grid[4], &endptrfl);
	if (endptrfl == grid[4] || obj->dt <= 0.0)
		return (ft_fprintf(2, "Parsing Err: No valid Cone height.\n"));
	if (ft_parse_color(&(obj->color), grid[5]))
		return (ft_fprintf(2, "Parsing Err: Colors in [0-255]\n"));
	node->type = 4;
	node->content = obj;
	ft_lstadd_back(&scene->objects, node);
	return (EXIT_SUCCESS);
}

int	ft_extract_co(t_scene *scene, char *line)
{
	char		**buffer;

	buffer = ft_spsplit(line, 0);
	if (!buffer || ft_split_count(buffer) != 6)
		return (ft_fprintf(2, "Parsing Err: extract Cone: Parameters\n"));
	if (buffer[0] && !ft_strcmp(buffer[0], "co"))
	{
		if (ft_save_co(scene, buffer))
			return (EXIT_FAILURE);
	}
	else
		return (ft_fprintf(2, "Parsing Err: saving Conr failed!\n"));
	return (EXIT_SUCCESS);
}
