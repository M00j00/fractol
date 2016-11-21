/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/20 07:30:54 by amanchon          #+#    #+#             */
/*   Updated: 2016/11/21 06:17:17 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "includes/libft.h"
# include "includes/mlx.h"
# include <math.h>
# include <pthread.h>

# define W_H 900
# define W_W 1300

# define DEFAULT_MAX_ITER 50
# define DEFAULT_MAX_RADIUS 4.0
# define DEFAULT_JULIA_R -0.8
# define DEFAULT_JULIA_I 0.2

# define NBCOLORS 64

# define BUTTON_PRESS_MASK (1L<<2)
# define BUTTON_RELEASE_MASK (1L<<3)
# define MOTION_NOTIFY_MASK (1L<<6)
# define BUTTON_PRESS 4
# define BUTTON_RELEASE 5
# define MOTION_NOTIFY 6

# define R 15
# define MOUSE_LOCK 37
# define RIGHT 124
# define LEFT 123
# define UP 126
# define DOWN 125
# define ESC 53
# define PLUS 69
# define MINUS 78
# define SCROLLUP 5
# define SCROLLDOWN 4

typedef int			t_iarr[2];
typedef double		t_darr[2];

typedef struct		s_img
{
	void			*ptr;
	int				bpp;
	int				line_size;
	int				endian;
	char			*pxl;
}					t_img;

typedef struct		s_env
{
	void			*mlx;
	void			*wnd;
	t_img			*img;
	int				colors[NBCOLORS];
	int				off_color;
	int				itermax;
	double			var[2];
	long double		zoom;
	long double		shift[2];
	int				lock;
	int				(*get_iter)(struct s_env *e, long double, long double);
}					t_env;

typedef struct		s_part
{
	t_iarr			start;
	t_iarr			end;
	t_env			*env;
	pthread_t		thread;
}					t_part;

t_img				*new_img(t_env *e, int w, int h);
int					refresh(t_env *e);
void				init_colors(t_env *e);
void				set_pixel_color(t_env *e, int x, int y, int i);
void				display_controls(t_env *e);

int					mandelbrot(t_env *e, long double x, long double y);
int					mandelquad(t_env *e, long double x, long double y);
int					julia(t_env *e, long double x, long double y);
int					burningship(t_env *e, long double x, long double y);

int					key_hook(int key, t_env *e);
int					mouse_btn(int btn, int x, int y, t_env *e);
int					mouse_move(int x, int y, t_env *e);

#endif
