/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddafter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeter <jpeter@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 12:43:24 by pdeson            #+#    #+#             */
/*   Updated: 2024/04/04 15:12:23 by jpeter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstaddafter(t_list *lst, t_list *new)
{
	t_list	*prev;
	t_list	*next;

	if (!lst || !new)
		return (NULL);
	next = lst;
	lst = lst->prev;
	prev = lst;
	lst->next = new;
	lst = lst->next;
	lst->prev = prev;
	lst->next = next;
	lst = next;
	lst->prev = new;
	return (lst);
}
