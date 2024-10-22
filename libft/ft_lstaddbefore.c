/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddbefore.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeter <jpeter@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 12:43:24 by pdeson            #+#    #+#             */
/*   Updated: 2024/04/15 10:28:00 by jpeter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstaddbefore(t_list *lst, t_list *new)
{
	t_list	*prev;
	t_list	*next;

	if (!lst || !new)
		return (NULL);
	prev = lst;
	next = lst->next;
	if (lst->next != NULL)
		lst->next->prev = new;
	lst->next = new;
	lst->next->prev = prev;
	lst->next->next = next;
	return (lst);
}
