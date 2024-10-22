/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_draw_img_parts.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:09:52 by pdeson            #+#    #+#             */
/*   Updated: 2024/10/18 10:16:32 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/mini_rt.h"

void	*renderthread(void *arg)
{
	t_taskqueue		*queue;
	t_rendertask	task;

	queue = (t_taskqueue *)arg;
	while (1)
	{
		if (dequeue(queue, &task) == 0)
		{
			if (task.startx == POISON_PILL_STARTX)
				break ;
			th_set_ray(&task);
			if (task.depth)
			{
				pthread_mutex_lock(&g_image->mut);
				ft_fprintf(1, "■");
				pthread_mutex_unlock(&g_image->mut);
			}
		}
		else
			break ;
	}
	return (NULL);
}

static t_color	ft_ptr_color(t_color ray, int color)
{
	return (ft_color_blend(0.5, ray, (t_color){get_red(color), \
		get_green(color), get_blue(color), get_alpha(color)}));
}

void	th_set_ray(t_rendertask *task)
{
	int				x;
	int				y;
	t_ray			*ray;
	t_color			ptr;

	y = task->starty;
	ray = ft_run_malloc(1, sizeof(t_ray));
	if (!ray)
		return ;
	while (y < task->starty + task->height)
	{
		x = task->startx;
		while (x < task->startx + task->width)
		{
			init_ray(task->scene, ray, (x + ft_rand()), (y + ft_rand()));
			ft_find_pixel_color(task->scene, ray);
			ptr = ft_ptr_color(ray->color, \
				g_image->pixels[x + (y * g_image->img_width)]);
			g_image->pixels[x + (y * g_image->img_width)] = def_intrgb(ptr);
			mlx_put_pixel(g_image->winptr, x, y, def_intrgb(ptr));
			x++;
		}
		y++;
	}
	return ;
}

void	th_launch_threads(t_scene *scene)
{
	pthread_t		threads[THREADS];
	t_taskqueue		queue;
	t_rendertask	*task;
	t_rendertask	poisonpill;
	int				i;

	task = ft_run_malloc(1, sizeof(t_rendertask));
	if (!task || !g_image->pixels)
		return ;
	initqueue(&queue);
	create_tasks(*task, &queue, scene);
	i = 0;
	while (i++ < THREADS)
	{
		poisonpill.startx = POISON_PILL_STARTX;
		enqueue(&queue, poisonpill);
	}
	i = 0;
	while (i < THREADS)
		pthread_create(&threads[i++], NULL, renderthread, &queue);
	i = 0;
	while (i < THREADS)
		pthread_join(threads[i++], NULL);
	ft_fprintf(1, "]\n");
	cleanupqueue(&queue);
}
