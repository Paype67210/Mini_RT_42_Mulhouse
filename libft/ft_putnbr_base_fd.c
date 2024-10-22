/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeter <jpeter@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 11:48:26 by philippe          #+#    #+#             */
/*   Updated: 2024/05/06 10:29:32 by jpeter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_verif_num(long long int nb, char format)
{
	if (format == 'u')
	{
		if (nb >= 0 && nb <= UINT_MAX)
			return (10);
	}
	else if (format == 'x' || format == 'X')
	{
		if (nb >= 0 && nb <= UINT_MAX)
			return (16);
	}
	return (-1);
}

int	ft_putnbr_base_fd(long int nb, char format, int fd)
{
	int		base;
	int		count;
	char	*ref;

	ref = "0123456789abcdef";
	base = ft_verif_num(nb, format);
	if (base == -1)
		return (-1);
	if (base == 16 && format == 'X')
		ref = "0123456789ABCDEF";
	count = 0;
	if (nb < 0)
	{
		count += ft_putchar_fd('-', fd);
		nb = -nb;
	}
	if (nb >= base)
	{
		count += ft_putnbr_base_fd(nb / base, format, fd);
		count += ft_putchar_fd(ref[nb % base], fd);
	}
	else
		count += ft_putchar_fd(ref[nb], fd);
	return (count);
}
