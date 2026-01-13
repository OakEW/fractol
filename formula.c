/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formula.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywang2 <ywang2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:53:46 by ywang2            #+#    #+#             */
/*   Updated: 2026/01/13 16:37:41 by ywang2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// z(n+1) = z(n) + c;
// z = jx + jy * i;
// c = a + b * i;
// a=argv[2] , b =argv[3];
void	make_julia(t_data *fractol, int x, int y)
{
	double	jx;
	double	jy;
	double	tmp;
	int		iteration;
	int		max_iter;

	jx = 2 * (x - fractol->w / 2) / (0.5 * fractol->zoom * fractol->w);
	jy = (y - fractol->h / 2) / (0.5 * fractol->zoom * fractol->h);
	iteration = 0;
	max_iter = 100 + (int)(log2(fractol->zoom) * 50);
	if (max_iter < 100)
		max_iter = 100;
	while (jx * jx + jy * jy <= 4 && iteration < max_iter)
	{
		tmp = jx * jx - jy * jy + fractol->ix;
		jy = 2 * jx * jy + fractol->iy;
		jx = tmp;
		iteration++;
	}
	color_pix(fractol, x, y, iteration);
}

// z(n+1) = z(n) + c;
// z(0) = 0 + 0 * i;
// c = zx + zy * i;
void	make_mandelbrot(t_data *fractol, int x, int y)
{
	double	tmp;
	int		i;
	double	zx;
	double	zy;

	i = 0;
	zx = 0.0;
	zy = 0.0;
	fractol->ix = 2 * (x - fractol->w / 2) / (0.5 * fractol->zoom * fractol->w);
	fractol->iy = (y - fractol->h / 2) / (0.5 * fractol->zoom * fractol->h);
	while (i < 100)
	{
		tmp = zx * zx - zy * zy + fractol->ix;
		zy = 2.0 * zx * zy + fractol->iy;
		zx = tmp;
		i++;
		if ((zx * zx + zy * zy) > 4)
			break ;
	}
	color_pix(fractol, x, y, i);
}
