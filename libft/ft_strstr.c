/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeter <jpeter@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:53:25 by pdeson            #+#    #+#             */
/*   Updated: 2024/05/10 11:18:19 by jpeter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strstr(char *str, char *value)
{
	size_t		i;
	size_t		j;

	if (value[0] == '\0' || !(str))
		return (-1);
	i = 0;
	str = ft_strjoin(" ", str);
	str = ft_strjoin(str, " ");
	value = ft_strjoin(" ", value);
	value = ft_strjoin(value, " ");
	while (str[i] != '\0')
	{
		j = 0;
		while (str[i++] == value[j++])
		{
			if (value[j] == '\0')
				return (i);
		}
		i = i - j;
		i++;
	}
	return (-1);
}

int	ft_strstr_without_space(const char *src, const char *value)
{
	size_t		i;
	size_t		j;

	i = 0;
	if (value[0] == '\0' || !(src))
		return (-1);
	while (src[i] != '\0')
	{
		{
			j = 0;
			while (src[i] == value[j])
			{
				j++;
				i++;
				if (value[j] == '\0')
					return (i);
			}
			i = i - j;
		}
		i++;
	}
	return (-1);
}
