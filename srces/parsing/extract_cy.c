/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_cy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:05:09 by pdeson            #+#    #+#             */
/*   Updated: 2024/10/18 09:21:56 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/mini_rt.h"

/* CYLENDER -> NODE.TYPE = 3 */

static int	ft_save_cy(t_scene *scene, char **grid)
{
	t_list	*node;
	t_obj	*obj;
	char	*endptrfl;

	obj = ft_run_malloc(1, sizeof(t_obj));
	node = ft_run_malloc(1, sizeof(t_list));
	if (!obj || !node)
		return (ft_fprintf(2, "Malloc failed: ft_save_cy\n"));
	if (ft_parse_vec3(grid[1], &(obj->coordos)))
		return (ft_fprintf(1, "Parsing Err: No valid Cylender position.\n"));
	if (ft_parse_vec3(grid[2], &(obj->vector)) || \
		vec3_length(obj->vector) > sqrt(3))
		return (ft_fprintf(2, "Parsing Err: No valid Cylender orientation.\n"));
	obj->dt = ft_strtod(grid[3], &endptrfl);
	if (endptrfl == grid[3] || obj->dt <= 0.0)
		return (ft_fprintf(2, "Parsing Err: No valid Cylender diam.\n"));
	obj->height = ft_strtod(grid[4], &endptrfl);
	if (endptrfl == grid[4] || obj->height <= 0.0)
		return (ft_fprintf(2, "Parsing Err: No valid Cylender height.\n"));
	if (ft_parse_color(&(obj->color), grid[5]))
		return (ft_fprintf(2, "Parsing Err: Colors in [0-255]\n"));
	node->type = 3;
	node->content = obj;
	ft_lstadd_back(&scene->objects, node);
	return (EXIT_SUCCESS);
}

int	ft_extract_cy(t_scene *scene, char *line)
{
	char		**buffer;

	buffer = ft_spsplit(line, 0);
	if (!buffer || ft_split_count(buffer) != 6)
		return (ft_fprintf(2, "Parsing Err: extract Cylender: Parameters\n"));
	if (buffer[0] && !ft_strcmp(buffer[0], "cy"))
	{
		if (ft_save_cy(scene, buffer))
			return (EXIT_FAILURE);
	}
	else
		return (ft_fprintf(2, "Parsing Err: saving Cylender failed!\n"));
	return (EXIT_SUCCESS);
}
