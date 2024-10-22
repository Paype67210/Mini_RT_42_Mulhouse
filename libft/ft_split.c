/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 09:37:04 by pdeson            #+#    #+#             */
/*   Updated: 2024/07/30 13:02:50 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_split_count(char **split)
{
	int	i;

	if (!split)
		return (-1);
	i = 0;
	while (split[i])
		i++;
	return (i);
}

char	**ft_gosplit(size_t len, char **array, char const *str, char c)
{
	size_t	i;
	size_t	j;
	int		index;

	i = 0;
	j = 0;
	index = -1;
	while (i <= len)
	{
		if (str[i] != c && index < 0 && i < len)
			index = i;
		else if ((str[i] == c || i == len) && index >= 0)
		{
			array[j] = ft_substr(str, index, i - index);
			if (!array[j])
				return (ft_free_array(&array), NULL);
			j++;
			index = -1;
		}
		i++;
	}
	array[j] = NULL;
	return (array);
}

char	**ft_split(char const *str, char c)
{
	char	**split;

	if (!str)
		exit (EXIT_FAILURE);
	split = ft_run_malloc(1, (ft_wcount(str, c) + 1) * sizeof(char *));
	if (!split)
	{
		ft_run_malloc(2, split);
		exit (EXIT_FAILURE);
	}
	split = ft_gosplit(ft_strlen(str), split, str, c);
	if (!split)
	{
		ft_run_malloc(2, split);
		exit (EXIT_FAILURE);
	}
	return (split);
}
