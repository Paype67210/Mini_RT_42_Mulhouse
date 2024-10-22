/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtof.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:22:09 by pdeson            #+#    #+#             */
/*   Updated: 2024/10/16 13:08:51 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

const char	*ft_parse_exp_part(const char *str, float *result)
{
	int	exp_sign;
	int	exponent;

	exp_sign = 1;
	exponent = 0;
	if (*str == 'e' || *str == 'E')
	{
		str++;
		if (*str == '-' || *str == '+')
		{
			if (*str == '-')
				exp_sign = -1;
			str++;
		}
		while (ft_isdigit(*str))
		{
			exponent = exponent * 10 + (*str - '0');
			str++;
		}
		if (exp_sign == -1)
			*result /= powf(10.0f, (float)exponent);
		else
			*result *= powf(10.0f, (float)exponent);
	}
	return (str);
}

float	ft_strtof(const char *str, char **endptr)
{
	float		result;
	float		power;
	int			sign;
	const char	*s;

	s = str;
	result = 0.0f;
	power = 1.0f;
	sign = 1;
	s = ft_skipspaces(s);
	s = ft_parse_sign(s, &sign);
	s = ft_parse_int_part(s, &result);
	s = ft_parse_fract_part(s, &result, &power);
	result = sign * result / power;
	s = ft_parse_exp_part(s, &result);
	if (endptr)
		*endptr = (char *)s;
	return (result);
}
