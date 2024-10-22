/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:50:47 by pdeson            #+#    #+#             */
/*   Updated: 2023/10/30 08:55:06 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char		*bufferdst;
	const char	*buffersrc;
	size_t		len;
	size_t		lendst;

	bufferdst = dst;
	buffersrc = src;
	len = size;
	while (*bufferdst != '\0' && len-- != 0)
		bufferdst++;
	lendst = bufferdst - dst;
	len = size - lendst;
	if (len == 0)
		return (lendst + ft_strlen(src));
	while (*buffersrc != '\0')
	{
		if (len != 1)
		{
			*bufferdst++ = *buffersrc;
			len--;
		}
		buffersrc++;
	}
	*bufferdst = '\0';
	return (lendst + (buffersrc - src));
}
