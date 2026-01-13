/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywang2 <ywang2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:53:57 by ywang2            #+#    #+#             */
/*   Updated: 2026/01/13 15:13:49 by ywang2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	rainbow_palette(t_data *fractol)
{
	int	i;
	int	r;
	int	g;
	int	b;

	i = 0;
	while (i < 256)
	{
		r = (int)(127 * (1 + sin(0.0245 * i)));
		g = (int)(127 * (1 + sin(0.0245 * i + 2)));
		b = (int)(127 * (1 + sin(0.0245 * i + 4)));
		fractol->palette[i] = (r << 16) | (g << 8) | b;
		i++;
	}
}

void	color_pix(t_data *fractol, int x, int y, int iteration)
{
	char	*dst;
	int		color;

	if (fractol->set == 1)
		iteration *= 13;
	color = fractol->palette[iteration % 256];
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
