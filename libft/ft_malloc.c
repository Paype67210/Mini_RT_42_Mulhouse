/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:15:47 by pdeson            #+#    #+#             */
/*   Updated: 2024/08/29 09:00:26 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	For ft_run_malloc, 1 = malloc, 2 = free, 3 = realloc, 4 = freeall
*/

void	*ft_malloc(t_list **ouille, size_t size)
{
	void	*buffer;
	t_list	*new_node;

	buffer = malloc(size);
	if (!buffer)
		return (NULL);
	new_node = malloc(sizeof(t_list));
	if (!new_node)
	{
		free(buffer);
		return (NULL);
	}
	ft_bzero(buffer, size);
	new_node->content = buffer;
	new_node->size = size;
	new_node->next = NULL;
	ft_lstadd_back(ouille, new_node);
	return (buffer);
}

int	*ft_realloc(t_list **list, void *ptr, size_t size)
{
	t_list	*current;
	void	*buffer;

	if (!list || !*list || !ptr)
		return (NULL);
	current = *list;
	while (current)
	{
		if (current->content == ptr)
		{
			buffer = realloc(ptr, size);
			if (!buffer)
				return (NULL);
			if (size > (unsigned long)current->size)
				ft_bzero((char *)buffer + current->size, size - current->size);
			current->content = buffer;
			current->size = size;
			return (current->content);
		}
		current = current->next;
	}
	return (NULL);
}

int	ft_free(t_list **ouille, void *ptr)
{
	t_list	*current;
	t_list	*prev;

	if (!ouille || !*ouille || !ptr)
		return (1);
	current = *ouille;
	prev = NULL;
	while (current)
	{
		if (current->content == ptr)
		{
			if (prev)
				prev->next = current->next;
			else
				*ouille = current->next;
			free(current->content);
			free(current);
			return (0);
		}
		prev = current;
		current = current->next;
	}
	return (1);
}

int	ft_freeall(t_list **ouille)
{
	t_list	*current;
	t_list	*next_node;

	if (!ouille || !*ouille)
		return (1);
	current = *ouille;
	while (current)
	{
		next_node = current->next;
		free(current->content);
		free(current);
		current = next_node;
	}
	*ouille = NULL;
	return (0);
}

void	*ft_run_malloc(int function, ...)
{
	static t_list	*g_ouille;
	va_list			args;
	void			*ptr;

	va_start(args, function);
	if (!g_ouille)
		g_ouille = NULL;
	if (function == 1)
		return (ft_malloc(&g_ouille, va_arg(args, size_t)));
	else if (function == 2)
	{
		ptr = va_arg(args, void *);
		if (ft_free(&g_ouille, ptr) == 1)
			return (ptr);
		return (NULL);
	}
	else if (function == 3)
		return (ft_realloc(&g_ouille, va_arg(args, void *), \
			va_arg(args, size_t)));
	else if (function == 4)
	{
		ft_freeall(&g_ouille);
		return (g_ouille);
	}
	return (va_end(args), NULL);
}
