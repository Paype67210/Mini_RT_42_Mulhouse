/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:10:43 by pdeson            #+#    #+#             */
/*   Updated: 2024/10/18 10:16:22 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/mini_rt.h" 

t_rendertask	ft_fill_task(t_scene *scene, int buffer, int i)
{
	t_rendertask	task;

	task.startx = i * (g_image->img_width / buffer);
	task.starty = 0;
	task.height = g_image->img_height;
	task.scene = scene;
	if (i == buffer - 1)
	{
		task.width = g_image->img_width - task.startx;
		task.depth = true;
	}
	else
	{
		task.width = g_image->img_width / buffer;
		task.depth = false;
	}
	return (task);
}

int	create_tasks(t_rendertask task, t_taskqueue *queue, t_scene *scene)
{
	int	i;
	int	j;
	int	maxiter;

	if (MAX_ITER > 1000)
		maxiter = 1000;
	else
		maxiter = MAX_ITER;
	j = 0;
	while (j < maxiter)
	{
		i = 0;
		while (i < (THREADS - 1))
		{
			task = ft_fill_task(scene, THREADS, i);
			enqueue(queue, task);
			i++;
		}
		task = ft_fill_task(scene, THREADS, i);
		task.count = j + 1;
		enqueue(queue, task);
		j++;
	}
	ft_fprintf(2, "Multithreading: %i Tasks created\n", i * j + 1);
	return (i * j);
}

t_color	ft_mix_color(t_ray *ray, uint32_t existing_pixel_color)
{
	t_color	new_color;
	double	rgba1[5];
	double	rgba2[5];

	rgba1[0] = (existing_pixel_color >> 24) & 0xFF;
	rgba1[1] = (existing_pixel_color >> 16) & 0xFF;
	rgba1[2] = (existing_pixel_color >> 8) & 0xFF;
	rgba1[3] = existing_pixel_color & 0xFF;
	rgba1[4] = '\0';
	rgba2[0] = ray->color.r;
	rgba2[1] = ray->color.g;
	rgba2[2] = ray->color.b;
	rgba2[3] = ray->color.a;
	rgba2[4] = '\0';
	new_color.r = (rgba1[0] * rgba1[3] + rgba2[0] * rgba2[3] * \
		(1 - rgba1[3])) / 255;
	new_color.g = (rgba1[1] * rgba1[3] + rgba2[1] * rgba2[3] * \
		(1 - rgba1[3])) / 255;
	new_color.b = (rgba1[2] * rgba1[3] + rgba2[2] * rgba2[3] * \
		(1 - rgba1[3])) / 255;
	new_color.a = rgba2[3];
	return (new_color);
}
