/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formula.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywang2 <ywang2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:53:46 by ywang2            #+#    #+#             */
/*   Updated: 2026/01/15 11:11:10 by ywang2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	mapping(t_data *f, int x, int y)
{
	f->re = 2 * (x - f->w / 2) / (0.5 * f->zoom * f->w) + f->off_x;
	f->im = (y - f->h / 2) / (0.5 * f->zoom * f->h) + f->off_y;
	f->max_iter = 100 + (int)(log2(f->zoom) * 50);
	if (f->max_iter < 100)
		f->max_iter = 100;
}

// z(n+1) = z(n)^2 + c;
// z = f->re + f->im * i  |  f->re f->im mapping(x, y);
// c = a + b * i          |  a = f->ix = argv[2] , b = f->iy = argv[3];
int	make_julia(t_data *f, int x, int y)
{
	double	tmp;
	int		i;

	mapping(f, x, y);
	i = 0;
	while (f->re * f->re + f->im * f->im <= 4 && i < f->max_iter)
	{
		tmp = f->re * f->re - f->im * f->im + f->ix;
		f->im = 2 * f->re * f->im + f->iy;
		f->re = tmp;
		i++;
	}
	return (i);
}

// z(n+1) = z(n)^2 + c;
// z(0) = 0 + 0 * i;      |  zx zy;
// c = f->re + f->im * i  |  f->re f->im mapping(x, y);
int	make_mandelbrot(t_data *f, int x, int y)
{
	double	tmp;
	int		i;
	double	zx;
	double	zy;

	i = 0;
	zx = 0.0;
	zy = 0.0;
	mapping(f, x, y);
	while ((zx * zx + zy * zy) <= 4 && i < f->max_iter)
	{
		tmp = zx * zx - zy * zy + f->re;
		zy = 2.0 * zx * zy + f->im;
		zx = tmp;
		i++;
	}
	return (i);
}

// z(n+1) = z(n)^4 + c;
// z(0) = 0 + 0 * i;      |  zx zy;
// c = f->re + f->im * i  |  f->re f->im mapping(x, y);
int	make_multibrot4(t_data *f, int x, int y)
{
	double	zx;
	double	zy;
	double	a;
	double	b;
	int		i;

	i = 0;
	zx = 0.0;
	zy = 0.0;
	mapping(f, x, y);
	while (zx * zx + zy * zy <= 4 && i < f->max_iter)
	{
		a = zx * zx * zx * zx - 6 * zx * zx * zy * zy + zy * zy * zy * zy;
		b = 4 * zx * zx * zx * zy - 4 * zx * zy * zy * zy;
		zx = a + f->re;
		zy = b + f->im;
		i++;
	}
	return (i);
}
