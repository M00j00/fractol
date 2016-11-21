/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 10:03:25 by amanchon          #+#    #+#             */
/*   Updated: 2016/11/21 06:26:03 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_img		*new_img(t_env *e, int width, int height)
{
	t_img			*img;

	if (!(img = (t_img*)malloc(sizeof(t_img))))
		return (NULL);
	img->ptr = mlx_new_image(e->mlx, width, height);
	img->pxl = mlx_get_data_addr(img->ptr, &img->bpp,
			&img->line_size, &img->endian);
	return (img);
}

void		set_pixel_color(t_env *e, int x, int y, int i)
{
	int				byte;
	int				color;

	byte = y * e->img->line_size + (e->img->bpp / 8) * x;
	if (i != e->itermax)
		color = e->colors[(i + e->off_color) % NBCOLORS];
	else
		color = 0;
	if (y < W_H && x < W_W && x > 0 && y > 0)
	{
		e->img->pxl[byte] = color;
		e->img->pxl[byte + 1] = color >> 8;
		e->img->pxl[byte + 2] = color >> 16;
	}
}

void		init_colors(t_env *e)
{
	int				i;
	float			alpha;
	unsigned char	c[3];

	alpha = 0;
	i = -1;
	while (++i < NBCOLORS)
	{
		c[0] = (unsigned char)((-cos(alpha) + 1.0) * 127.0);
		c[1] = (unsigned char)((sin(alpha) + 1) * 127);
		c[2] = (unsigned char)((cos(alpha) + 1) * 127);
		e->colors[i] = ((int)c[0]) << 16 | ((int)c[1]) << 8 | ((int)c[2]);
		alpha += 2 * M_PI / NBCOLORS;
	}
}
