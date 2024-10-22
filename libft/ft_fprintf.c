/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: philippe <philippe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 11:58:09 by ajordan-          #+#    #+#             */
/*   Updated: 2024/04/24 09:02:53 by philippe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_fformats(va_list args, const char format, int fd_log)
{
	int	count;

	count = 0;
	if (format == 'c')
		count += ft_putchar_fd(va_arg(args, int), fd_log);
	else if (format == 's')
		count += ft_putstr_fd(va_arg(args, char *), fd_log);
	else if (format == 'p')
		count += ft_putptr_fd(va_arg(args, unsigned long long), fd_log);
	else if (format == 'd' || format == 'i')
		count += ft_putnbr_fd(va_arg(args, int), fd_log);
	else if (format == 'u' || format == 'x' || format == 'X')
		count += ft_putnbr_base_fd(va_arg(args, long int), format, fd_log);
	else if (format == '%')
		count += ft_putchar_fd('%', fd_log);
	return (count);
}

int	ft_fprintf(int fd_log, const char *format, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			count += ft_fformats(args, *format, fd_log);
		}
		else
			count += ft_putchar_fd(*format, fd_log);
		format++;
	}
	va_end(args);
	return (count);
}
