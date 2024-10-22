/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_vp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:37:10 by pdeson            #+#    #+#             */
/*   Updated: 2024/10/16 12:34:56 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/mini_rt.h"

int	def_intrgb(t_color color)
{
	int	buffer;

	buffer = 0;
	buffer |= color.r << 24;
	buffer |= color.g << 16;
	buffer |= color.b << 8;
	buffer |= color.a;
	return (buffer);
}

void	init_ray(t_scene *scene, t_ray *ray, double x, double y)
{
	ray->origin = vec3_add(g_image->vp->pixel00, \
		vec3_add(vec3_scale(g_image->vp->delta_u, x), \
		vec3_scale(g_image->vp->delta_v, y)));
	ray->direct = scene->camera->vect_norm;
	ray->color = (t_color){0, 0, 0, 255};
	ray->depth = 0;
	return ;
}

int	ft_render(t_scene *scene)
{
	int		x;
	int		y;
	t_ray	*ray;
	int		pixel_index;

	y = 0;
	ray = ft_run_malloc(1, sizeof(t_ray));
	if (!ray)
		return (ft_fprintf(2, "Malloc failed: ft_render\n"));
	while (y < g_image->img_height)
	{
		x = 0;
		while (x < g_image->img_width)
		{
			init_ray(scene, ray, x, y);
			ft_find_pixel_color(scene, ray);
			pixel_index = (int)(y * g_image->img_width + x);
			g_image->pixels[pixel_index] = def_intrgb(ray->color);
			mlx_put_pixel(g_image->winptr, x, y, g_image->pixels[pixel_index]);
			x++;
		}
		y++;
	}
	return (0);
}

int	ft_launch_vp(t_scene *scene)
{
	g_image->mlxptr = mlx_init(g_image->img_width, g_image->img_height, \
		"Mini_RT", false);
	if (!g_image->mlxptr)
		return (ft_fprintf(2, mlx_strerror(mlx_errno)));
	g_image->winptr = mlx_new_image(g_image->mlxptr, g_image->img_width, \
		g_image->img_height);
	if (!g_image->winptr)
	{
		mlx_close_window(g_image->mlxptr);
		return (ft_fprintf(2, mlx_strerror(mlx_errno)));
	}
	if (mlx_image_to_window(g_image->mlxptr, g_image->winptr, 0, 0) == -1)
	{
		mlx_close_window(g_image->mlxptr);
		return (puts(mlx_strerror(mlx_errno)));
	}
	g_image->pixels = ft_run_malloc(1, sizeof(int32_t) * \
		g_image->img_height * g_image->img_width);
	if (!g_image->pixels)
		return (ft_fprintf(2, "Malloc failed: ft_launch_vp\n"));
	mlx_loop_hook(g_image->mlxptr, ft_hook, scene);
	mlx_mouse_hook(g_image->mlxptr, ft_mouse, scene);
	mlx_loop(g_image->mlxptr);
	return (EXIT_SUCCESS);
}
