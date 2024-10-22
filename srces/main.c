/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:01:48 by pdeson            #+#    #+#             */
/*   Updated: 2024/10/18 08:59:04 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/mini_rt.h"

t_img	*g_image;

static int	ft_init_malloc(t_scene *scene)
{
	scene->ambiant = ft_run_malloc(1, sizeof(t_ambiant));
	scene->camera = ft_run_malloc(1, sizeof(t_camera));
	scene->lights = ft_run_malloc(1, sizeof(t_list));
	scene->objects = ft_run_malloc(1, sizeof(t_list));
	g_image->vp = ft_run_malloc(1, sizeof(t_viewport));
	if (!scene->ambiant || !scene->camera || !scene->lights || !scene->objects \
		|| !g_image->vp)
		return (ft_msg("Error: ", "Malloc failed", NULL, EXIT_FAILURE));
	return (EXIT_SUCCESS);
}

int	ft_init_scene(t_scene *scene)
{
	if (ft_init_malloc(scene))
		return (EXIT_FAILURE);
	scene->save = false;
	scene->calc = false;
	scene->ok = false;
	scene->end = false;
	g_image->vp_height = 0;
	g_image->vp_width = 0;
	g_image->img_height = 0;
	g_image->img_width = 0;
	g_image->vp->ratio = -1;
	srand(time(NULL));
	return (EXIT_SUCCESS);
}

int	init(t_scene *scene)
{
	int		fd_log;

	errno = 0;
	ft_open_stderr(&fd_log);
	if (dup2(fd_log, STDERR_FILENO) == -1 || close(fd_log) == -1)
		return (ft_msg("Error 418: ", "I'm a teapot", \
			"i cannot make coffee!", EXIT_FAILURE));
	g_image = ft_run_malloc(1, sizeof(t_img));
	if (!g_image)
		return (ft_msg("Error: ", "Malloc failed", NULL, EXIT_FAILURE));
	if (ft_init_scene(scene))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	int			status;
	t_scene		scene;

	status = 0;
	signal(SIGTERM, ft_handle_signal);
	if (argc < 2 || argc > 3)
		return (ft_msg("Error: ", "Bad Arguments: ", NULL, EXIT_FAILURE));
	if (init(&scene))
		return (ft_msg("Error: ", "Creation scene failed", NULL, 1));
	if (argc == 3 && argv[2])
	{
		if (!verif_bmp_name(&scene, argv[2]))
			return (ft_msg("Error: ", "Saving_file: ", \
				"invalid file name", EXIT_FAILURE));
	}
	if (argc == 2 || argc == 3 || !argv[1])
		status = ft_check_file(&scene, argv[1]);
	else
		ft_fprintf(2, "Error: Bad Arguments: ./mini_rt file.rt [exit.bmp]\n");
	if (!status)
	{
		if (ft_viewport(&scene))
			status = ft_fprintf(2, "miniRT arrete sans rendering!\n");
	}
	return (ft_exit(&scene, status));
}
