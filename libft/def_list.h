/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def_list.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:40:13 by pdeson            #+#    #+#             */
/*   Updated: 2024/10/16 13:09:34 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEF_LIST_H
# define DEF_LIST_H

typedef struct s_list
{
	void			*content;
	int				type;
	size_t			size;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;

#endif
