/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 09:07:25 by amanchon          #+#    #+#             */
/*   Updated: 2016/11/21 06:27:16 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			mouse_btn(int btn, int x, int y, t_env *e)
{
	if (btn == SCROLLUP)
	{
		e->zoom *= 1.5;
		e->shift[0] += (x - W_W / 2) / e->zoom;
		e->shift[1] -= (y - W_H / 2) / e->zoom;
	}
	else if (btn == SCROLLDOWN)
		e->zoom /= 2;
	refresh(e);
	return (0);
}

int			mouse_move(int x, int y, t_env *e)
{
	if (!e->lock)
	{
		x -= W_W / 2;
		y -= W_H / 2;
		e->var[0] = ((double)x / W_W);
		e->var[1] = ((double)y / W_H);
	}
	refresh(e);
	return (0);
}

int			key_hook(int key, t_env *e)
{
	if (key == ESC)
	{
		mlx_destroy_window(e->mlx, e->wnd);
		exit(0);
	}
	else if (key == MOUSE_LOCK)
		e->lock = !e->lock;
	else if (key == UP)
		e->shift[1] += 20.0;
	else if (key == DOWN)
		e->shift[1] -= 20.0;
	else if (key == RIGHT)
		e->shift[0] += 20.0;
	else if (key == LEFT)
		e->shift[0] -= 20.0;
	else if (key == PLUS)
		e->itermax += 10;
	else if (key == MINUS)
		e->itermax -= 10;
	else if (key == R)
		e->off_color += 5;
	refresh(e);
	return (0);
}
