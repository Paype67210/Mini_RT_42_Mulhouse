/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 11:22:09 by pdeson            #+#    #+#             */
/*   Updated: 2024/07/31 09:24:24 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static const char	*ft_parse_intpart(const char *str, double *result)
{
	while (ft_isdigit(*str))
	{
		*result = *result * 10.0 + (*str - '0');
		str++;
	}
	return (str);
}

double	ft_strtod(const char *str, char **endptr)
{
	int			sign;
	double		result;
	double		fraction;
	const char	*s;

	result = 0.0;
	fraction = 1.0;
	sign = 1;
	s = str;
	s = ft_skipspaces(s);
	s = ft_parse_sign(s, &sign);
	s = ft_parse_intpart(s, &result);
	if (*s == '.')
	{
		s++;
		while (ft_isdigit(*s))
		{
			fraction *= 0.1;
			result += (*s - '0') * fraction;
			s++;
		}
	}
	if (endptr != NULL)
		*endptr = (char *)s;
	return (sign * result);
}
