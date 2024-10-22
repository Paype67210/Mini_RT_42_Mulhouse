/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_cam.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:14:04 by pdeson            #+#    #+#             */
/*   Updated: 2024/10/18 09:14:47 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/mini_rt.h"

static int	ft_save_cam(t_scene *scene, char **grid)
{
	if (ft_parse_vec3(grid[1], &(scene->camera->coordos)))
		return (ft_fprintf(1, "Parsing Err: No valid cam position.\n"));
	if (ft_parse_vec3(grid[2], &(scene->camera->vect_norm)) || \
		vec3_length(scene->camera->vect_norm) > sqrt(3))
		return (ft_fprintf(2, "Parsing Err: No valid cam direction.\n"));
	scene->camera->fov = ft_atoi(grid[3]);
	if (scene->camera->fov <= 0 || scene->camera->fov > 180)
		return (ft_fprintf(2, "Parsing Err: No valid cam FOV.\n"));
	return (EXIT_SUCCESS);
}

int	ft_extract_cam(t_scene *scene, char *line)
{
	char	**buffer;

	if (scene->camera->exist)
		return (ft_msg("Parsing Err: ", "Too many C Id.", NULL, 1));
	buffer = ft_spsplit(line, 0);
	if (!buffer || ft_split_count(buffer) != 4)
		return (ft_fprintf(2, "Parsing Err: extract cam: Parameters\n"));
	if (buffer[0] && !ft_strcmp(buffer[0], "C"))
	{
		if (ft_save_cam(scene, buffer))
			return (EXIT_FAILURE);
	}
	else
		return (ft_fprintf(2, "Parsing Err: saving Cam failed!\n"));
	scene->camera->exist = true;
	scene->trashcoordos = &scene->camera->coordos;
	scene->trashvector = &scene->camera->vect_norm;
	ft_fprintf(2, "Camera definition OK!\n");
	return (EXIT_SUCCESS);
}
