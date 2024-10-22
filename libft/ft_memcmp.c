/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 08:50:00 by pdeson            #+#    #+#             */
/*   Updated: 2023/10/30 10:29:41 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str, const void *s2, size_t n)
{
	const unsigned char	*s1;
	const unsigned char	*s2b;

	s1 = str;
	s2b = s2;
	while (n--)
	{
		if (*s1 != *s2b)
			return (*s1 - *s2b);
		s1++;
		s2b++;
	}
	return (0);
}
