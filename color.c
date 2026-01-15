/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywang2 <ywang2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:53:57 by ywang2            #+#    #+#             */
/*   Updated: 2026/01/15 12:25:24 by ywang2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	animate(void *param)
{
	t_data	*f;
	int		x;
	int		y;

	f = (t_data *)param;
	if (f->animate < 0)
		return (0);
	f->shift += 0.01;
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
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
	return (0);
}

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
