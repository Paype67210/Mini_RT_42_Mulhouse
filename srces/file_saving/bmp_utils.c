/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:51:39 by pdeson            #+#    #+#             */
/*   Updated: 2024/09/16 14:18:03 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/mini_rt.h"

void	ft_create_file_header(t_bmp_file_header *file_header, int file_size)
{
	file_header->bf_type = 0x4D42;
	file_header->bf_size = file_size;
	file_header->bf_reserved1 = 0;
	file_header->bf_reserved2 = 0;
	file_header->bf_off_bits = 14 + 40;
	return ;
}

void	ft_create_info_header(t_bmp_info_header *info_header)
{
	info_header->bi_size = 40;
	info_header->bi_width = g_image->img_width;
	info_header->bi_height = -g_image->img_height;
	info_header->bi_planes = 1;
	info_header->bi_bit_count = 32;
	info_header->bi_compression = 0;
	info_header->bi_size_image = g_image->img_width * g_image->img_height * 4;
	info_header->bi_x_pels_per_meter = 3780;
	info_header->bi_y_pels_per_meter = 3780;
	info_header->bi_clr_used = 0;
	info_header->bi_clr_important = 0;
	return ;
}
