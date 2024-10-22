/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save_to_bmp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:28:52 by pdeson            #+#    #+#             */
/*   Updated: 2024/10/02 08:30:59 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/mini_rt.h"

int	verif_bmp_name(t_scene *scene, const char *filename)
{
	int	i;

	i = 0;
	while (filename[i])
	{
		if (ft_isprint(filename[i]) == 0)
			return (0);
		i++;
	}
	if (i < 5)
		return (0);
	if (filename[i - 1] != 'p' || filename[i - 2] != 'm' \
		|| filename[i - 3] != 'b' || filename[i - 4] != '.')
		return (0);
	scene->file = filename;
	scene->save = true;
	return (1);
}

int	write_bmp_headers(int fd_bmp)
{
	t_bmp_file_header	file_header;
	t_bmp_info_header	info_header;
	int					file_size;

	file_size = 14 + 40 + (g_image->img_width * g_image->img_height * 4);
	ft_create_file_header(&file_header, file_size);
	ft_create_info_header(&info_header);
	if (write(fd_bmp, &file_header, sizeof(file_header)) == -1)
		return (ft_msg("Error: ", "Saving_file: ", \
			"write failed", EXIT_FAILURE));
	if (write(fd_bmp, &info_header, sizeof(info_header)) == -1)
		return (ft_msg("Error: ", "Saving_file: ", \
			"write failed", EXIT_FAILURE));
	return (EXIT_SUCCESS);
}

int	write_bmp_pixels(int fd_bmp)
{
	int			y;
	int			x;
	uint32_t	color;

	printf("Saving file ...");
	y = 0;
	while (y < g_image->img_height)
	{
		x = 0;
		while (x < g_image->img_width)
		{
			color = ft_rgba_to_barg(g_image->pixels[y * \
				g_image->img_width + x]);
			if (write(fd_bmp, &color, 4) == -1)
				return (ft_msg("Error: ", "Saving_file: ", \
					"write failed", EXIT_FAILURE));
			x++;
		}
		y++;
	}
	printf("\nDone\n");
	return (EXIT_SUCCESS);
}

uint32_t	ft_rgba_to_barg(uint32_t color)
{
	int	buffer;

	buffer = 0;
	buffer |= (color) << 24;
	buffer |= (color >> 24) << 16;
	buffer |= (color >> 16) << 8;
	buffer |= (color >> 8);
	return (buffer);
}

int	save_bmp(const char *filename)
{
	int	fd_bmp;

	fd_bmp = open(filename, O_WRONLY | O_CREAT | O_TRUNC | O_BINARY, 0666);
	if (fd_bmp < 0)
		return (ft_msg("Error: ", "Saving_file: ", \
			"create file failed", EXIT_FAILURE));
	if (write_bmp_headers(fd_bmp))
		return (EXIT_FAILURE);
	if (write_bmp_pixels(fd_bmp))
		return (EXIT_FAILURE);
	if (close(fd_bmp) == -1)
		return (ft_msg("Error: ", "Saving_file: ", \
			"close file failed", EXIT_FAILURE));
	return (EXIT_SUCCESS);
}
