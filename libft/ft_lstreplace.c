/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeter <jpeter@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:10:47 by pdeson            #+#    #+#             */
/*   Updated: 2024/04/19 11:49:49 by jpeter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
	Replace a node in a list with another node.
	return 1 if the node was found and replaced, 0 otherwise.
*/

int	ft_lstreplace(t_list **lst, t_list *node)
{
	t_list	*buffer;

	buffer = *lst;
	while (buffer && buffer != node)
		buffer = buffer->next;
	if (buffer)
	{
		if (buffer->prev)
			buffer->prev->next = node;
		else
			*lst = node;
		if (buffer->next)
			buffer->next->prev = node;
		node->next = buffer->next;
		node->prev = buffer->prev;
		ft_run_malloc(2, buffer);
		return (1);
	}
	return (0);
}
