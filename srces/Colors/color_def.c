/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_def.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:09:47 by pdeson            #+#    #+#             */
/*   Updated: 2024/10/16 11:47:48 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/mini_rt.h"

t_color	ft_color_blend(double f, t_color c1, t_color c2)
{
	t_color	buffer;

	if (f < -1.0)
		f = -1.0;
	else if (f > 1.0)
		f = 1.0;
	if (f < 0)
	{
		buffer = ft_define_colors((1.0 + f) * c1.r, \
			(1.0 + f) * c1.g, (1.0 + f) * c1.b);
	}
	else
	{
		f = pow(f, 2.5);
		buffer = ft_define_colors((1.0 - f) * c1.r + f * c2.r, \
			(1.0 - f) * c1.g + f * c2.g, (1.0 - f) * c1.b + f * c2.b);
	}
	buffer.r = fmin(fmax(buffer.r, 0), 255);
	buffer.g = fmin(fmax(buffer.g, 0), 255);
	buffer.b = fmin(fmax(buffer.b, 0), 255);
	buffer.a = 255;
	return (buffer);
}

t_color	ft_define_colors(int32_t r, int32_t g, int32_t b)
{
	return ((t_color){r, g, b, 255});
}

t_color	ft_color_scale(double f, t_color color)
{
	t_color	buffer;

	buffer.r = fmin(fmax(f * color.r, 0), 255);
	buffer.g = fmin(fmax(f * color.g, 0), 255);
	buffer.b = fmin(fmax(f * color.b, 0), 255);
	buffer.a = 255;
	return (buffer);
}

int	ft_str_to_int(const char *str, uint32_t min, uint32_t max, uint32_t *resol)
{
	int	i;

	i = 0;
	if ((str[0] == '+' || str[0] == '-') && str[1] != '\0')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	*resol = ft_atoi(str);
	if (*resol < min || *resol > max)
		return (-1);
	return (0);
}

int	ft_parse_color(t_color *color, const char *str)
{
	char		**split;
	uint32_t	prim;
	int			error;

	split = ft_split(str, ',');
	if (!split)
		return (-1);
	prim = 0;
	error = (ft_split_count(split) != 3);
	if (!error)
		error = ft_str_to_int(split[0], 0, 255, &prim);
	(*color).r = prim;
	if (!error)
		error = ft_str_to_int(split[1], 0, 255, &prim);
	(*color).g = prim;
	if (!error)
		error = ft_str_to_int(split[2], 0, 255, &prim);
	(*color).b = prim;
	(*color).a = 255;
	ft_run_malloc(2, split);
	return (error);
}
