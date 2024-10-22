/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strbtwcpy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 09:37:04 by pdeson            #+#    #+#             */
/*   Updated: 2024/04/16 13:44:18 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strbtwcpy(char *str, char chr1, char chr2)
{
	char	*dst;
	int		i;
	int		j;
	int		k;

	i = 0;
	while (str[i] != chr1)
		i++;
	j = (i + 1);
	while (str[j] != chr2)
		j++;
	dst = ft_run_malloc(1, (j - i) * sizeof(char));
	if (!dst)
		return (NULL);
	k = 0;
	while (++i != j)
		dst[k++] = str[i];
	dst[k] = '\0';
	return (dst);
}
