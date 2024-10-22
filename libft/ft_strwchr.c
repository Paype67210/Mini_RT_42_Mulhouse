/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strwchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeter <jpeter@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 08:50:00 by pdeson            #+#    #+#             */
/*   Updated: 2024/06/21 11:51:37 by jpeter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strwchr(char *str, char chr)
{
	char	*result;
	int		i;
	int		nbr;

	i = 0;
	nbr = 0;
	while (str[i++] != '\0')
	{
		if (str[i] != chr)
			nbr++;
	}
	result = ft_run_malloc(1, (nbr + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	nbr = 0;
	while (str[i] != '\0')
	{
		if (str[i] != chr)
			result[nbr++] = str[i];
		i++;
	}
	result[nbr] = '\0';
	return (result);
}
