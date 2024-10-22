/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_end.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 08:53:40 by pdeson            #+#    #+#             */
/*   Updated: 2024/02/12 08:58:57 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_char_end(char *str, char n)
{
	size_t	len;

	len = 0;
	len = ft_strlen(str) - 1;
	while (str[len] != n && len > 0)
		len --;
	return (len);
}
