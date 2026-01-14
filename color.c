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
	double	n;

	n = 0.03;
	f = (t_data *)param;
	if (f->set == 1)
		n = 0.04;
	else if (f->set == 3)
		n = 0.06;
	if (f->animate < 0)
		return (0);
	f->shift += n;
	rainbow_palette(f);
	ft_render(f);
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
	int		i;

	i = iteration;
	if (fractol->set != 2)
		i = 10.0 * sqrt((double)iteration);
	color = fractol->palette[i % 256];
	if (fractol->set != 2 && iteration == fractol->max_iter
		&& fractol->palette_set > 0)
		color = 0x00100030;
	dst = fractol->addr + (y * fractol->line_length
			+ x * (fractol->bits_per_pixel / 8));
	if (*(unsigned int *)dst != (unsigned int)color)
		*(unsigned int *)dst = (unsigned int)color;
}

void	ft_render(t_data *fractol)
{
	int	x;
	int	y;

	x = 0;
	while (x < fractol->w)
	{
		y = 0;
		while (y < fractol->h)
		{
			if (fractol->set == 3)
				make_multibrot4(fractol, x, y);
			if (fractol->set == 2)
				make_julia(fractol, x, y);
			if (fractol->set == 1)
				make_mandelbrot(fractol, x, y);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(fractol->mlx, fractol->win, fractol->img, 0, 0);
}
