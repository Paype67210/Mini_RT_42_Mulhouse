/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcopy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:54:04 by pdeson            #+#    #+#             */
/*   Updated: 2024/07/29 15:58:19 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstcopy(t_list *lst)
{
	t_list	*new_list;
	t_list	*temp;

	new_list = NULL;
	while (lst)
	{
		temp = ft_lstnew(lst->content);
		if (!temp)
			return (NULL);
		ft_lstadd_back(&new_list, temp);
		lst = lst->next;
	}
	return (new_list);
}
