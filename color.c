/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywang2 <ywang2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:53:57 by ywang2            #+#    #+#             */
/*   Updated: 2026/01/15 11:09:55 by ywang2           ###   ########.fr       */
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
	rainbow_palette(f);
	x = 0;
	while (x < f->w)
	{
		y = 0;
		while (y < f->h)
		{
			*(unsigned int *)(f->addr + (y * f->line_length + x
						* (f->bits_per_pixel / 8)))
				= f->palette[f->color_index[y * f->w + x]];
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
	return (0);
}

void	rainbow_palette(t_data *fractol)
{
	int		x;
	int		r;
	int		g;
	int		b;
	int		n;

	x = 0;
	n = 2;
	if (fractol->palette_set < 0)
		n = 0;
	while (x < 256)
	{
		r = (int)(127 * (1 + sin(x * 0.04 + fractol->shift)));
		g = (int)(127 * (1 + sin(x * 0.04 + fractol->shift + n)));
		b = (int)(127 * (1 + sin(x * 0.04 + fractol->shift + n + n)));
		fractol->palette[x] = (r << 16) | (g << 8) | b;
		x++;
	}
}

void	color_pix(t_data *fractol, int x, int y, int iteration)
{
	char	*dst;
	int		color;

	color = fractol->palette[fractol->color_index[y * fractol->w + x]];
	if (fractol->set != 2 && iteration == fractol->max_iter
		&& fractol->palette_set > 0)
		color = 0x00100030;
	dst = fractol->addr + (y * fractol->line_length
			+ x * (fractol->bits_per_pixel / 8));
	*(unsigned int *)dst = (unsigned int)color;
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
			f->color_index[y * f->w + x] = i % 256;
			if (f->set != 2)
				f->color_index[y * f->w + x] = (int)(10.0 * sqrt(i)) % 256;
			color_pix(f, x, y, i);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
}
