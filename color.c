/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywang2 <ywang2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:53:57 by ywang2            #+#    #+#             */
/*   Updated: 2026/01/13 16:41:58 by ywang2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	rainbow_palette(t_data *fractol)
{
	int	i;
	int	r;
	int	g;
	int	b;
	double phase;

	i = 0;
	phase = 1.3;
	while (i < 256)
	{
		r = (int)(127 * (1 + sin(0.04 * i + phase)));
		g = (int)(127 * (1 + sin(0.04 * i + phase + 2)));
		b = (int)(127 * (1 + sin(0.04 * i + phase + 4)));
		fractol->palette[i] = (r << 16) | (g << 8) | b;
		i++;
	}
}

void	color_pix(t_data *fractol, int x, int y, int iteration)
{
	char	*dst;
	int		color;

	if (fractol->set == 1)
		iteration = 10.0 * sqrt((double)iteration);
	color = fractol->palette[iteration % 256];
	if (fractol->set == 1 && iteration >= 100)
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

void	clean_up(t_data *fractol)
{
	mlx_destroy_image(fractol->mlx, fractol->img);
	mlx_destroy_window(fractol->mlx, fractol->win);
	mlx_destroy_display(fractol->mlx);
	free (fractol->mlx);
}
