/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 08:50:00 by pdeson            #+#    #+#             */
/*   Updated: 2023/10/18 11:18:13 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *mtr, int c, size_t n)
{
	unsigned char	*p;
	unsigned char	value;
	size_t			i;

	p = mtr;
	value = (unsigned char)c;
	i = 0;
	while (i < n)
		p[i++] = value;
	return (p);
}
