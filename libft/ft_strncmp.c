/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 12:50:47 by pdeson            #+#    #+#             */
/*   Updated: 2023/10/26 16:44:36 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (str[i] && i < n && (str[i] == s2[i]))
		i++;
	if (i == n || (str[i] == s2[i]) || (n == 0))
		return (0);
	return ((unsigned char)str[i] - (unsigned char)s2[i]);
}
