/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeter <jpeter@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:46:39 by jpeter            #+#    #+#             */
/*   Updated: 2024/04/11 11:10:48 by jpeter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strnchr(const char *src, int value, size_t i)
{
	while (src[i] != '\0')
	{
		if (src[i] == (unsigned char)value)
		{
			return ((char *)&src[i]);
		}
		i++;
	}
	return (NULL);
}
