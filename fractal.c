/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 07:52:05 by amanchon          #+#    #+#             */
/*   Updated: 2016/11/21 06:15:34 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int					julia(t_env *e, long double x, long double y)
{
	long double		r;
	long double		im;
	long double		tmp;
	int				i;

	r = ((4.0 * x / W_W - 2.0) / e->zoom) + ((e->shift[0] / W_W));
	im = ((-3.0 * y / W_H + 1.5) / e->zoom) + ((e->shift[1] / W_H));
	i = -1;
	while (r * r + im * im <= DEFAULT_MAX_RADIUS && ++i < e->itermax)
	{
		tmp = r;
		r = r * r - im * im + e->var[0];
		im = 2 * tmp * im + e->var[1];
	}
	return (i);
}

int					mandelbrot(t_env *e, long double r, long double im)
{
	long double		x;
	long double		y;
	long double		xtmp;
	long double		ytmp;
	int				i;

	r = ((3.0 * r / W_W - 2.0) / e->zoom) + (e->shift[0] / W_W);
	im = ((-2.0 * im / W_H + 1.0) / e->zoom) + (e->shift[1] / W_H);
	x = 0;
	y = 0;
	i = -1;
	while (x * x + y * y <= DEFAULT_MAX_RADIUS && ++i < e->itermax)
	{
		xtmp = x * x - y * y + r;
		ytmp = 2 * x * y + im;
		if (x == xtmp && y == ytmp)
			i = e->itermax - 1;
		x = xtmp;
		y = ytmp;
	}
	return (i);
}

int					mandelquad(t_env *e, long double r, long double im)
{
	long double		x;
	long double		y;
	long double		xtmp;
	long double		ytmp;
	int				i;

	r = ((3.0 * r / W_W - 2.0) / e->zoom) + (e->shift[0] / W_W);
	im = ((-2.0 * im / W_H + 1.0) / e->zoom) + (e->shift[1] / W_H);
	x = 0;
	y = 0;
	i = -1;
	while (x * x + y * y <= DEFAULT_MAX_RADIUS && ++i < e->itermax)
	{
		xtmp = (x * x * x * x) - (6 * x * x * y * y) + (y * y * y * y) + r;
		ytmp = (4 * x * x * x * y) - (4 * x * y * y * y) + im;
		if (x == xtmp && y == ytmp)
			i = e->itermax - 1;
		x = xtmp;
		y = ytmp;
	}
	return (i);
}

int					burningship(t_env *e, long double r, long double im)
{
	long double		x;
	long double		y;
	long double		xtmp;
	long double		ytmp;
	int				i;

	r = ((4.0 * r / W_W - 2.0) / e->zoom) + (e->shift[0] / W_W);
	im = ((-4.0 * (1 - im / W_H) + 2.0) / e->zoom) - (e->shift[1] / W_H);
	x = 0;
	y = 0;
	i = -1;
	while (x * x + y * y <= DEFAULT_MAX_RADIUS && ++i < e->itermax)
	{
		xtmp = fabsl(x) * fabsl(x) - fabsl(y) * fabsl(y) + r;
		ytmp = 2 * fabsl(x) * fabsl(y) + im;
		if (x == xtmp && y == ytmp)
			i = e->itermax - 1;
		x = xtmp;
		y = ytmp;
	}
	return (i);
}
