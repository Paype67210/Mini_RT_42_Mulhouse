/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 10:56:53 by pdeson            #+#    #+#             */
/*   Updated: 2024/10/16 13:14:52 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/mini_rt.h"

int	ft_check_file(t_scene *scene, char *file)
{
	char	*str;
	int		len;
	char	*buffer;

	buffer = NULL;
	len = ft_strlen(file);
	str = file + (len - 3);
	if (ft_strncmp(str, ".rt", 3))
		buffer = "Bad file extension";
	if (!buffer && access(file, F_OK))
		buffer = "File does not exist";
	if (!buffer && access(file, R_OK))
		buffer = "Access denied";
	if (!buffer && ft_parse_file(scene, file))
		buffer = "Parsing Error";
	if (buffer)
		return (ft_msg("Error: ", "File: ", buffer, EXIT_FAILURE));
	return (EXIT_SUCCESS);
}

int	ft_parse_file(t_scene *scene, char *file)
{
	char	*buffer;

	scene->fd = open(file, O_RDONLY);
	if (scene->fd == -1)
	{
		ft_fprintf(2, "Error: ft_parse_file: %s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	buffer = ft_run_malloc(1, sizeof(char *));
	if (!buffer)
		return (ft_msg("Error: ", "Malloc GNL failed", NULL, EXIT_FAILURE));
	if (ft_extract_params(scene, buffer, 1))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_extract_params(t_scene *scene, char *line, int status)
{
	line = get_next_line(scene->fd);
	while (line)
	{
		if (!ft_strncmp(line, "R", 1))
			status = ft_extract_resol(line);
		else if (!ft_strncmp(line, "A ", 1))
			status = ft_extract_amb(scene, line);
		else if (!ft_strncmp(line, "C ", 1))
			status = ft_extract_cam(scene, line);
		else if (!ft_strncmp(line, "L ", 1))
			status = ft_extract_lights(scene, line);
		else if (!ft_strncmp(line, "sp ", 2))
			status = ft_extract_sp(scene, line);
		else if (!ft_strncmp(line, "pl ", 2))
			status = ft_extract_pl(scene, line);
		else if (!ft_strncmp(line, "cy ", 2))
			status = ft_extract_cy(scene, line);
		else if (!ft_strncmp(line, "co ", 2))
			status = ft_extract_co(scene, line);
		line = get_next_line(scene->fd);
	}
	if (status || ft_validation_scene(scene))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_validation_scene(t_scene *scene)
{
	t_list	*buffer;
	t_obj	*tmp;

	if (!scene->ambiant->exist || !scene->camera->exist || \
		ft_lstsize(scene->lights) == 0 || ft_lstsize(scene->objects) == 0)
		return (ft_fprintf(2, "Error: Scene does not exist!"));
	buffer = ft_lstfirst(scene->objects);
	while (buffer)
	{
		tmp = buffer->content;
		tmp->color = ft_color_blend(scene->ambiant->ratio, tmp->color, \
			scene->ambiant->color);
		if (scene_light_weights(scene->lights))
			return (ft_fprintf(2, "Error: lights does not exist!"));
		buffer = buffer->next;
	}
	return (EXIT_SUCCESS);
}
