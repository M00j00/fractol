/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 08:21:06 by amanchon          #+#    #+#             */
/*   Updated: 2016/11/21 05:52:55 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void			*draw_part(void *data)
{
	int			x;
	int			y;
	t_part		*p;

	p = (t_part*)data;
	y = p->start[1] - 1;
	while (y++ < p->end[1])
	{
		x = p->start[0] - 1;
		while (++x < p->end[0])
			set_pixel_color(p->env, x, y, p->env->get_iter(p->env, x, y));
	}
	return (NULL);
}

static void			draw_all_screen_parts(t_env *e)
{
	t_part		parts[4];
	int			i;

	i = -1;
	while (++i < 4)
	{
		parts[i].start[0] = (W_W / 2) * (i % 2);
		parts[i].start[1] = (W_H / 2) * (i / 2);
		parts[i].end[0] = (W_W / 2) * (i % 2 + 1);
		parts[i].end[1] = (W_H / 2) * (i / 2 + 1);
		parts[i].env = e;
		pthread_create(&(parts[i].thread), NULL, draw_part, (void*)&parts[i]);
	}
	i = -1;
	while (++i < 4)
		pthread_join(parts[i].thread, NULL);
}

void				display_controls(t_env *e)
{
	if (e->get_iter == julia)
	{
		ft_putendl("Bouger la souris pour changer le param de Julia");
		ft_putendl("L pour des/activer la souris");
	}
	ft_putendl("Fleches pour deplacer limage\nR pour changer la couleur");
	ft_putendl("numpad + et - pour changer l iter max");
	ft_putendl("Molette pour zoomer");
}

int					refresh(t_env *e)
{
	draw_all_screen_parts(e);
	mlx_clear_window(e->mlx, e->wnd);
	mlx_put_image_to_window(e->mlx, e->wnd, e->img->ptr, 0, 0);
	return (0);
}
