/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtof_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:39:18 by pdeson            #+#    #+#             */
/*   Updated: 2024/09/16 14:25:58 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

const char	*ft_skipspaces(const char *str)
{
	while (ft_isspace(*str))
		str++;
	return (str);
}

const char	*ft_parse_sign(const char *str, int *sign)
{
	*sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			*sign = -1;
		str++;
	}
	return (str);
}

const char	*ft_parse_int_part(const char *str, float *result)
{
	while (ft_isdigit(*str))
	{
		*result = *result * 10.0f + (*str - '0');
		str++;
	}
	return (str);
}

const char	*ft_parse_fract_part(const char *str, float *result, float *power)
{
	if (*str == '.')
	{
		str++;
		while (ft_isdigit(*str))
		{
			*result = *result * 10.0f + (*str - '0');
			*power *= 10.0f;
			str++;
		}
	}
	return (str);
}
