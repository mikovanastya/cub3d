/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:57:40 by majacqua          #+#    #+#             */
/*   Updated: 2022/07/27 14:13:38 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	render(t_env *env)
{
	t_img	*frame;
	t_vect	**rays;
	int		i;

	i = 0;
	frame = new_img(env->mlx);// создаем новое изображение
	rays = raycasting(env);// массив лучей, от героя до стен
	render_walls(env, rays, frame);// стены
	render_minimap(env, frame);// миникарта
	mlx_put_image_to_window(env->mlx, env->win, frame->img_ptr, 0, 0);// кладем изображение в окно
	free_img(env->mlx, frame);// очищаем изображение
	while (i < RES_X)// очищаем изображение
		free(rays[i++]);
	free(rays);
}

int	get_fog_color(int options, int color, double distance)
{
	double	fog_grade;

	fog_grade = distance / FOG_GRADE;
	if (options)
	{
		if (fog_grade <= 1.0)
			return (color);
		return (((int)(((0xFF0000 & color) >> 16) / fog_grade) << 16)
			+ ((int)(((0x00FF00 & color) >> 8) / fog_grade) << 8)
			+ ((int)((0x0000FF & color) / fog_grade)));
	}
	return (color);
}
