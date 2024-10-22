/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   th_task_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeter <jpeter@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 09:37:43 by pdeson            #+#    #+#             */
/*   Updated: 2024/10/04 10:32:31 by jpeter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/mini_rt.h"

void	initqueue(t_taskqueue *queue)
{
	queue->head = NULL;
	queue->tail = NULL;
	pthread_mutex_init(&queue->lock, NULL);
	pthread_mutex_init(&g_image->mut, NULL);
	if (pthread_cond_init(&queue->cond, NULL))
	{
		ft_msg("Error: ", "Cond init failed", NULL, EXIT_FAILURE);
		return ;
	}
}

void	enqueue(t_taskqueue *queue, t_rendertask task)
{
	t_node	*newtask;

	newtask = (t_node *)ft_run_malloc(1, sizeof(t_node));
	if (!newtask)
	{
		ft_msg("Error: ", "Malloc failed", NULL, EXIT_FAILURE);
		return ;
	}
	newtask->task = task;
	newtask->next = NULL;
	pthread_mutex_lock(&queue->lock);
	if (queue->tail == NULL)
	{
		queue->head = newtask;
		queue->tail = newtask;
	}
	else
	{
		queue->tail->next = newtask;
		queue->tail = newtask;
	}
	pthread_cond_signal(&queue->cond);
	pthread_mutex_unlock(&queue->lock);
}

int	dequeue(t_taskqueue *queue, t_rendertask *task)
{
	t_node	*temp;

	pthread_mutex_lock(&queue->lock);
	while (queue->head == NULL)
		pthread_cond_wait(&queue->cond, &queue->lock);
	temp = queue->head;
	*task = temp->task;
	queue->head = queue->head->next;
	if (queue->head == NULL)
		queue->tail = NULL;
	ft_run_malloc(2, temp);
	pthread_mutex_unlock(&queue->lock);
	return (0);
}

void	cleanupqueue(t_taskqueue *queue)
{
	t_node	*current;
	t_node	*tmp;

	pthread_mutex_lock(&queue->lock);
	current = queue->head;
	while (current != NULL)
	{
		tmp = current;
		current = current->next;
		ft_run_malloc(2, tmp);
	}
	pthread_mutex_unlock(&queue->lock);
	pthread_mutex_destroy(&queue->lock);
	pthread_mutex_destroy(&g_image->mut);
	pthread_cond_destroy(&queue->cond);
}
