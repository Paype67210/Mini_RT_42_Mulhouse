/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 08:50:00 by pdeson            #+#    #+#             */
/*   Updated: 2024/04/16 13:42:04 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	memsize;

	if (nmemb == 0 || size == 0)
		return (ft_run_malloc(1, 0));
	memsize = nmemb * size;
	if (memsize / size != nmemb)
		return (NULL);
	ptr = ft_run_malloc(1, size * nmemb);
	if (!ptr)
		return (NULL);
	else
		ft_memset(ptr, 0, memsize);
	return (ptr);
}
