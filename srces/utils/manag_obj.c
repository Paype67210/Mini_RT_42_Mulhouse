/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manag_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdeson <pdeson@student.42mulhouse.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 09:47:49 by pdeson            #+#    #+#             */
/*   Updated: 2024/10/16 11:48:05 by pdeson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/mini_rt.h"

t_obj	*obj_cont(t_list *list)
{
	return ((t_obj *)list->content);
}

t_rendertask	*render_cont(t_list *list)
{
	return ((t_rendertask *)list->content);
}

double	ft_rand(void)
{
	return ((double)((rand() % 100) / 200.0));
}

t_scene	*scene_cont(void *scene)
{
	return ((t_scene *)scene);
}
