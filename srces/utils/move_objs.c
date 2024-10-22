/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_objs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:36:56 by pdeson            #+#    #+#             */
/*   Updated: 2024/10/18 09:05:08 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/mini_rt.h"

static void	ft_move1(t_scene *scene)
{
	int	delta;

	delta = 40;
	if (mlx_is_key_down(g_image->mlxptr, MLX_KEY_LEFT_SHIFT))
		delta *= -1;
	if (mlx_is_key_down(g_image->mlxptr, MLX_KEY_Q))
		scene->trashcoordos->x += delta;
	if (mlx_is_key_down(g_image->mlxptr, MLX_KEY_W))
		scene->trashcoordos->y += delta;
	if (mlx_is_key_down(g_image->mlxptr, MLX_KEY_E))
		scene->trashcoordos->z += delta;
	return ;
}

// ft_move2 permet de changer le vecteur de la caméra ou de l'objet sélectionné

static void	ft_move2(t_scene *scene)
{
	double	delta;

	delta = 0.2;
	if (mlx_is_key_down(g_image->mlxptr, MLX_KEY_LEFT_SHIFT))
		delta *= -1;
	if (mlx_is_key_down(g_image->mlxptr, MLX_KEY_A))
		scene->trashvector->x = ft_vector_turn(scene->trashvector->x, delta);
	if (mlx_is_key_down(g_image->mlxptr, MLX_KEY_S))
		scene->trashvector->y = ft_vector_turn(scene->trashvector->y, delta);
	if (mlx_is_key_down(g_image->mlxptr, MLX_KEY_D))
		scene->trashvector->z = ft_vector_turn(scene->trashvector->z, delta);
	return ;
}
// ft_move3 permet de zommer ou dézoomer dans le champs de vision de la caméra

static void	ft_move3(t_scene *scene)
{
	if (mlx_is_key_down(g_image->mlxptr, MLX_KEY_P))
		ft_prt_draw_size(scene);
	if (mlx_is_key_down(g_image->mlxptr, MLX_KEY_UP))
		ft_cam_move_bf(scene, 200);
	if (mlx_is_key_down(g_image->mlxptr, MLX_KEY_DOWN))
		ft_cam_move_bf(scene, -200);
	return ;
}

static int	ft_verif_key(void)
{
	if (mlx_is_key_down(g_image->mlxptr, MLX_KEY_Q) || \
		mlx_is_key_down(g_image->mlxptr, MLX_KEY_W) || \
		mlx_is_key_down(g_image->mlxptr, MLX_KEY_E))
		return (1);
	if (mlx_is_key_down(g_image->mlxptr, MLX_KEY_A) || \
		mlx_is_key_down(g_image->mlxptr, MLX_KEY_S) || \
		mlx_is_key_down(g_image->mlxptr, MLX_KEY_D))
		return (2);
	else if (mlx_is_key_down(g_image->mlxptr, MLX_KEY_P) || \
		mlx_is_key_down(g_image->mlxptr, MLX_KEY_UP) || \
		mlx_is_key_down(g_image->mlxptr, MLX_KEY_DOWN))
		return (3);
	return (0);
}

void	ft_hook(void *scene)
{
	t_scene	*buffer;

	buffer = scene;
	if (mlx_is_key_down(g_image->mlxptr, MLX_KEY_ESCAPE))
	{
		ft_fprintf(2, "Close window\n");
		mlx_close_window(g_image->mlxptr);
	}
	if (mlx_is_key_down(g_image->mlxptr, MLX_KEY_R) && !buffer->calc)
	{
		buffer->calc = true;
		ft_fprintf(1, "Lancement du rendering!\n");
		ft_launch_render(scene);
	}
	if (!buffer->calc && ft_verif_key() == 1)
		ft_move1(scene);
	if (!buffer->calc && ft_verif_key() == 2)
		ft_move2(scene);
	if (!buffer->calc && ft_verif_key() == 3)
		ft_move3(scene);
	if (!scene_cont(scene)->end)
		ft_hook2(scene);
	return ;
}
