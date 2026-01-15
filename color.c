/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywang2 <ywang2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:53:57 by ywang2            #+#    #+#             */
/*   Updated: 2026/01/15 18:51:57 by ywang2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

unsigned int	make_color(t_data *f, int i)
{
	int		r;
	int		g;
	int		b;
	int		n;
	double	x;

	if (f->set != 2 && i >= f->max_iter && f->palette_set > 0)
		return (0x00100030);
	x = (double)i / f->max_iter;
	if (f->set != 2)
		x = sqrt(x);
	n = 2;
	if (f->palette_set < 0)
		n = 0;
	r = (int)(127 * (1 + sin(x * 6 + f->shift)));
	g = (int)(127 * (1 + sin(x * 6 + f->shift + n)));
	b = (int)(127 * (1 + sin(x * 6 + f->shift + n + n)));
	return ((r << 16) | (g << 8) | b);
}

int	animate(void *param)
{
	t_data	*f;
	int		x;
	int		y;

	f = (t_data *)param;
	if (f->gradient > 0)
		f->shift += 0.05;
	x = 0;
	while (x < f->w)
	{
		y = 0;
		while (y < f->h)
		{
			*(unsigned int *)(f->addr + (y * f->line_length + x
						* (f->bits_per_pixel / 8)))
				= make_color(f, f->iter[y * f->w + x]);
			y++;
		}
		x++;
	}
	if (f->autoj > 0 && f->set == 2)
		auto_julia(f);
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
	return (0);
}

void	recal_julia(t_data *f)
{
	static double	t;
	static int		init;
	double			r;

	r = sqrt(f->ix * f->ix + f->iy * f->iy);
	if (!init)
	{
		t = atan2(f->iy, f->ix);
		init = 1;
	}
	t += 0.005;
	f->ix = r * cos(t);
	f->iy = r * sin(t);
}

void	auto_julia(t_data *f)
{
	int	x;
	int	y;
	int	i;

	recal_julia(f);
	x = 0;
	while (x < f->w)
	{
		y = 0;
		while (y < f->h)
		{
			i = make_julia(f, x, y);
			f->iter[y * f->w + x] = i;
			*(unsigned int *)(f->addr + (y * f->line_length + x
						* (f->bits_per_pixel / 8)))
				= make_color(f, f->iter[y * f->w + x]);
			y++;
		}
		x++;
	}
}

void	ft_render(t_data *f)
{
	int	x;
	int	y;
	int	i;

	x = 0;
	while (x < f->w)
	{
		y = 0;
		while (y < f->h)
		{
			if (f->set == 3)
				i = make_multibrot4(f, x, y);
			else if (f->set == 2)
				i = make_julia(f, x, y);
			else if (f->set == 1)
				i = make_mandelbrot(f, x, y);
			f->iter[y * f->w + x] = i;
			*(unsigned int *)(f->addr + (y * f->line_length + x
						* (f->bits_per_pixel / 8)))
				= make_color(f, f->iter[y * f->w + x]);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
}
