/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_j.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywang2 <ywang2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:53:57 by ywang2            #+#    #+#             */
/*   Updated: 2026/01/16 16:06:20 by ywang2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	recal_julia(t_data *f)
{
	static int		init;
	static double	c;
	static double	s;
	double			cos_o;
	double			sin_o;

	if (!init)
	{
		c = cos(0.002);
		s = sin(0.002);
		init = 1;
	}
	cos_o = f->ix;
	sin_o = f->iy;
	f->ix = c * cos_o - s * sin_o;
	f->iy = s * cos_o + c * sin_o;
}

void	update_julia(t_data *f)
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
			y++;
		}
		x++;
	}
}
