/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:08:29 by pdeson            #+#    #+#             */
/*   Updated: 2024/03/18 18:13:32 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstremove(t_list **lst, t_list *node, void (*del)(void*))
{
	t_list	*i_token;

	i_token = *lst;
	while (i_token && i_token != node)
		i_token = i_token->next;
	if (i_token)
	{
		if (i_token->prev)
			i_token->prev->next = i_token->next;
		else
			*lst = i_token->next;
		if (i_token->next)
			i_token->next->prev = i_token->prev;
		ft_lstdelone(i_token, del);
		return (1);
	}
	return (0);
}
