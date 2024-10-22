/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeter <jpeter@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:34:22 by pdeson            #+#    #+#             */
/*   Updated: 2024/04/19 11:50:42 by jpeter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *str, size_t len)
{
	size_t	i;
	char	*buffer;

	i = 0;
	buffer = ft_run_malloc(1, sizeof(char) * (len + 1));
	while (i < len && str[i])
	{
		buffer[i] = str[i];
		i++;
	}
	while (i < len)
		buffer[i++] = '\0';
	return (buffer);
}
