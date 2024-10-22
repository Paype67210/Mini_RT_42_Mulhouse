/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnlcpy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:50:47 by pdeson            #+#    #+#             */
/*   Updated: 2024/04/16 13:47:15 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnlcpy(const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	char	*dst;

	j = size;
	i = 0;
	dst = ft_run_malloc(1, (ft_strlen(src) - size + 1) * sizeof(char));
	while (j != ft_strlen(src))
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dst);
}
