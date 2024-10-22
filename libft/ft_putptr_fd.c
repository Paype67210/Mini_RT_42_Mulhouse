/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeter <jpeter@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 13:20:43 by ajordan-          #+#    #+#             */
/*   Updated: 2024/05/06 10:28:44 by jpeter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putnbrptr_fd(unsigned long long ptr, char format, int fd)
{
	int		count;
	char	*ref;

	ref = "0123456789abcdef";
	if (format == 'X')
		ref = "0123456789ABCDEF";
	count = 0;
	if (ptr >= 16)
		count += ft_putnbrptr_fd(ptr / 16, format, fd);
	count += ft_putchar_fd(ref[ptr % 16], fd);
	return (count);
}

int	ft_putptr_fd(unsigned long long ptr, int fd)
{
	int	count;

	count = 0;
	if (ptr <= 0)
		return (ft_putstr_fd(PTRNULL, fd));
	count += ft_putstr_fd("0x", fd);
	count += ft_putnbrptr_fd(ptr, 'x', fd);
	return (count);
}
