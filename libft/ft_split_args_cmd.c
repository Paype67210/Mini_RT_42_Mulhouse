/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_args_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 09:37:04 by pdeson            #+#    #+#             */
/*   Updated: 2024/04/16 13:53:27 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_split_args_cmd(char const *str)
{
	char	**array;
	int		i;

	if (!str)
		exit (EXIT_FAILURE);
	if (ft_int_strchr(str, '\'') < 0)
		array = ft_split(str, ' ');
	else
		array = ft_split(str, '\'');
	if (!array)
	{
		ft_run_malloc(2, array);
		exit (EXIT_FAILURE);
	}
	else
	{
		i = 0;
		while (array[i])
		{
			array[i] = ft_strtrim(array[i], " ");
			i++;
		}
	}
	return (array);
}
