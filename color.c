/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywang2 <ywang2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:53:57 by ywang2            #+#    #+#             */
/*   Updated: 2026/01/14 18:39:33 by ywang2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	animate(void *param)
{
	t_data	*f;
	int		x;
	int		y;
	int		idx;

	f = (t_data *)param;
	if (f->animate < 0)
		return (0);
	f->shift += 0.03;
	rainbow_palette(f);
	x = 0;
	while (x < f->w)
	{
		y = 0;
		while (y < f->h)
		{
			idx = y * f->w + x;
			*(unsigned int *)(f->addr + (y * f->line_length
				+ x * (f->bits_per_pixel / 8))) = f->palette[f->color_index[idx]];
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
	return (0);
}

void	rainbow_palette(t_data *fractol)
{
	int		i;
	int		r;
	int		g;
	int		b;
	int		n;

	i = 0;
	n = 2;
	if (fractol->palette_set < 0)
		n = 0;
	while (i < 256)
	{
		r = (int)(127 * (1 + sin(0.04 * i + fractol->shift)));
		g = (int)(127 * (1 + sin(0.04 * i + fractol->shift + n)));
		b = (int)(127 * (1 + sin(0.04 * i + fractol->shift + n + n)));
		fractol->palette[i] = (r << 16) | (g << 8) | b;
		i++;
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

void	ft_render(t_data *fractol)
{
	int	x;
	int	y;
	int	idx;
	int	iteration;
	int	cidx;

	x = 0;
	while (x < fractol->w)
	{
		y = 0;
		while (y < fractol->h)
		{
			if (fractol->set == 3)
				iteration = make_multibrot4(fractol, x, y);
			else if (fractol->set == 2)
				iteration = make_julia(fractol, x, y);
			else if (fractol->set == 1)
				iteration = make_mandelbrot(fractol, x, y);
			idx = y * fractol->w + x;
			cidx = iteration % 256;
			if (fractol->set != 2)
				cidx = (int)(10.0 * sqrt(iteration)) % 256;
			fractol->color_index[idx] = cidx;
			color_pix(fractol, x, y, iteration);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img, 0, 0);
}
