/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_rgb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpeter <jpeter@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:40:06 by pdeson            #+#    #+#             */
/*   Updated: 2024/09/10 10:24:09 by jpeter           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/mini_rt.h"

uint32_t	rgb_to_int(unsigned char r, unsigned char g, \
	unsigned char b, unsigned char a)
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

// Fonction pour extraire la valeur rouge d'un entier RGBA
unsigned char	get_red(uint32_t color)
{
	return ((color >> 24) & 0xFF);
}

// Fonction pour extraire la valeur verte d'un entier RGBA
unsigned char	get_green(uint32_t color)
{
	return ((color >> 16) & 0xFF);
}

// Fonction pour extraire la valeur bleue d'un entier RGBA
unsigned char	get_blue(uint32_t color)
{
	return ((color >> 8) & 0xFF);
}

// Fonction pour extraire la valeur alpha d'un entier RGBA
unsigned char	get_alpha(uint32_t color)
{
	return (color & 0xFF);
}
