/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: philippe <philippe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:04:55 by pdeson            #+#    #+#             */
/*   Updated: 2024/04/24 09:03:55 by philippe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_fd(int nb, int fd)
{
	unsigned int	nbr;
	int				count;

	count = 0;
	if (nb < 0)
	{
		count += ft_putchar_fd('-', fd);
		nbr = (unsigned int)(-nb);
	}
	else
		nbr = (unsigned int)nb;
	if (nbr >= 10)
		count += ft_putnbr_fd(nbr / 10, fd);
	count += ft_putchar_fd((char)(nbr % 10 + '0'), fd);
	return (count);
}
