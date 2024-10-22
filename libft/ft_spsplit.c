/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spsplit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 09:37:04 by pdeson            #+#    #+#             */
/*   Updated: 2024/07/30 10:26:33 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_words(const char *str)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (ft_isspace(*str))
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		str++;
	}
	return (count);
}

char	**ft_spsplit(char const *str, int word_index)
{
	int			num_words;
	char		**result;
	char		*start;

	num_words = count_words(str);
	result = ft_run_malloc(1, (num_words + 1) * sizeof(char *));
	start = NULL;
	while (*str)
	{
		if (ft_isspace(*str))
		{
			if (start)
			{
				result[word_index++] = ft_strncpy(start, str - start);
				start = NULL;
			}
		}
		else if (!start)
			start = (char *)str;
		str++;
	}
	if (start)
		result[word_index++] = ft_strncpy(start, str - start);
	result[word_index] = NULL;
	return (result);
}
