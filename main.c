/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 08:45:46 by amanchon          #+#    #+#             */
/*   Updated: 2016/11/21 06:16:51 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int			init(t_env *e)
{
	if (!(e->mlx = mlx_init()))
		return (0);
	if (!(e->wnd = mlx_new_window(e->mlx, W_W, W_H, "fractol@42")))
		return (0);
	if (!(e->img = new_img(e, W_W, W_H)))
		return (0);
	display_controls(e);
	init_colors(e);
	e->lock = 0;
	e->shift[0] = 0;
	e->shift[1] = 0;
	e->zoom = 1.0;
	e->itermax = DEFAULT_MAX_ITER;
	e->off_color = 0;
	return (1);
}

static int			get_param(t_env *e, char *str)
{
	if (ft_strequ("M", str))
		e->get_iter = mandelbrot;
	if (ft_strequ("J", str))
	{
		e->get_iter = julia;
		e->var[0] = DEFAULT_JULIA_R;
		e->var[1] = DEFAULT_JULIA_I;
	}
	if (ft_strequ("M4", str))
		e->get_iter = mandelquad;
	if (ft_strequ("BS", str))
		e->get_iter = burningship;
	return (e->get_iter == 0 ? 0 : 1);
}

int					main(int argc, char **argv)
{
	t_env		*e;

	if (!(e = (t_env*)ft_memalloc(sizeof(t_env))))
		return (0);
	if (argc != 2 || !get_param(e, argv[1]))
	{
		ft_putendl("Usage: ./fractol <M/J/BS/M4>");
		return (0);
	}
	if (!(init(e)))
		return (0);
	refresh(e);
	mlx_expose_hook(e->wnd, refresh, e);
	mlx_key_hook(e->wnd, key_hook, e);
	mlx_hook(e->wnd, BUTTON_PRESS, BUTTON_PRESS_MASK, mouse_btn, e);
	if (e->get_iter == julia)
		mlx_hook(e->wnd, MOTION_NOTIFY, MOTION_NOTIFY_MASK, mouse_move, e);
	mlx_loop(e->mlx);
}
