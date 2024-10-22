/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:31:12 by pdeson            #+#    #+#             */
/*   Updated: 2024/10/18 08:34:47 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/mini_rt.h"

void	ft_print_object_list2(t_scene *scene, \
	t_list *buffer, t_obj *tmp, int count)
{
	(void)scene;
	if (buffer->type == 1)
		dprintf(2, "%i. Sphere:\n", count);
	else if (buffer->type == 2)
	{
		dprintf(2, "%i. Plane:\n", count);
		dprintf(2, "\tVect: x [%.2f], y [%.2f], z [%.2f]\n", \
			tmp->vector.x, tmp->vector.y, tmp->vector.z);
	}
	else if (buffer->type == 3)
	{
		dprintf(2, "%i. Cylender:\n", count);
		dprintf(2, "\tVect: x [%.2f], y [%.2f], z [%.2f]\n", \
			tmp->vector.x, tmp->vector.y, tmp->vector.z);
	}
	else if (buffer->type == 4)
	{
		dprintf(2, "%i. Cone:\n", count);
		dprintf(2, "\tVect: x [%.2f], y [%.2f], z [%.2f]\n", \
			tmp->vector.x, tmp->vector.y, tmp->vector.z);
	}
}

int	ft_print_object_list(t_scene *scene)
{
	t_list	*buffer;
	int		count;
	t_obj	*tmp;

	if (!scene)
		return (EXIT_FAILURE);
	count = 1;
	buffer = ft_lstfirst(scene->objects);
	while (buffer)
	{
		tmp = buffer->content;
		ft_print_object_list2(scene, buffer, tmp, count);
		dprintf(2, "\tCoordos: x [%.2f], y [%.2f], z [%.2f]\n", \
			tmp->coordos.x, tmp->coordos.y, tmp->coordos.z);
		dprintf(2, "\tColors: R [%i], G [%i], B [%i] (a [%i])\n", \
			tmp->color.r, tmp->color.g, tmp->color.b, tmp->color.a);
		if (tmp->dt)
			dprintf(2, "\tDiametre: %.2f\n", tmp->dt);
		if (tmp->height)
			dprintf(2, "\tHauteur: %.2f\n", tmp->height);
		count++;
		buffer = buffer->next;
	}
	return (EXIT_SUCCESS);
}

int	ft_print_debug(t_scene *scene)
{
	t_list	*buffer;
	int		count;
	t_obj	*tmp;

	if (!scene)
		return (EXIT_FAILURE);
	count = 1;
	buffer = ft_lstfirst(scene->lights);
	while (buffer)
	{
		tmp = buffer->content;
		dprintf(2, "Light %i:\n", count);
		dprintf(2, "\tCoordos: x [%.2f], y [%.2f], z [%.2f]\n", \
			tmp->coordos.x, tmp->coordos.y, tmp->coordos.z);
		count++;
		buffer = buffer->next;
	}
	return (EXIT_SUCCESS);
}

void	ft_prt_draw_size(t_scene *scene)
{
	(void)scene;
	printf("VP: [W %i x H %i]\n", g_image->vp_width, g_image->vp_height);
	printf("Camera: [%.1f, %.1f, %.1f]", \
		scene->camera->coordos.x, scene->camera->coordos.y, \
		scene->camera->coordos.z);
	printf(" - Direction: [%.1f, %.1f, %.1f]\n", \
		scene->camera->vect_norm.x, scene->camera->vect_norm.y, \
		scene->camera->vect_norm.z);
	printf("Ratio = %.5f", g_image->vp->ratio);
	printf(" / Focale = %.2f\n", g_image->vp->focal);
	printf("VP u: [%.1f, %.1f, %.1f]\n", \
		g_image->vp->vp_u.x, g_image->vp->vp_u.y, g_image->vp->vp_u.z);
	printf("VP v: [%.1f, %.1f, %.1f]\n", \
		g_image->vp->vp_v.x, g_image->vp->vp_v.y, g_image->vp->vp_v.z);
	printf("Img_Center: [%.1f, %.1f, %.1f]\n", \
		g_image->vp->img_center.x, g_image->vp->img_center.y, \
		g_image->vp->img_center.z);
	printf("Pixel00: [%.1f, %.1f, %.1f]\n", \
		g_image->vp->pixel00.x, g_image->vp->pixel00.y, g_image->vp->pixel00.z);
	printf("Delta U: [%.4f, %.4f, %.4f]\n", \
		g_image->vp->delta_u.x, g_image->vp->delta_u.y, g_image->vp->delta_u.z);
	printf("Delta V: [%.4f, %.4f, %.4f]\n", \
		g_image->vp->delta_v.x, g_image->vp->delta_v.y, g_image->vp->delta_v.z);
	printf("DrawWindow: [W %i x H %i]\n", \
		g_image->img_width, g_image->img_height);
}
