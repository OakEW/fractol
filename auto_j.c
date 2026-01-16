/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_j.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywang2 <ywang2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:53:57 by ywang2            #+#    #+#             */
/*   Updated: 2026/01/16 12:19:57 by ywang2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	recal_julia(t_data *f)
{
	static double	t;
	static int		init;
	double			r;

	f->max_iter = 100 + (int)(log2(f->zoom) * 50);
	if (f->max_iter < 100)
		f->max_iter = 100;
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
