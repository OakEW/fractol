/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywang2 <ywang2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:53:54 by ywang2            #+#    #+#             */
/*   Updated: 2026/01/14 17:29:09 by ywang2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	close_x(t_data *fractol)
{
	mlx_loop_end(fractol->mlx);
	return (0);
}

int	key_do_1(int key, t_data *fractol)
{
	if (key == 97 || key == 100 || key == 119)
	{
		if (key == 119)
			fractol->palette_set *= -1;
		else if (key == 100)
			fractol->shift += 0.1;
		else if (key == 97)
			fractol->shift -= 0.1;
		rainbow_palette(fractol);
		ft_render(fractol);
	}
	else if (key == 65307)
		mlx_loop_end(fractol->mlx);
	return (0);
}

int	key_do_2(int key, t_data *fractol)
{
	if (key == 105)
		fractol->ix += 0.01;
	else if (key == 107)
		fractol->ix -= 0.01;
	else if (key == 111)
		fractol->iy += 0.01;
	else if (key == 108)
		fractol->iy -= 0.01;
	else if (key == 115)
		fractol->animate *= -1;
	else if (key == 65361)
		fractol->off_x += 0.1 / fractol->zoom;
	else if (key == 65363)
		fractol->off_x -= 0.1 / fractol->zoom;
	else if (key == 65362)
		fractol->off_y += 0.1 / fractol->zoom;
	else if (key == 65364)
		fractol->off_y -= 0.1 / fractol->zoom;
	else
		return (0);
	ft_render(fractol);
	return (0);
}

int	key_do_all(int key, t_data *fractol)
{
	key_do_1(key, fractol);
	key_do_2(key, fractol);
	return (0);
}

int	mouse_do(int mousecode, int x, int y, t_data *f)
{
	double	m_re;
	double	m_im;
	double	zoomer;

	m_re = 2 * (x - f->w / 2.0) / (0.5 * f->zoom * f->w) + f->off_x;
	m_im = (y - f->h / 2.0) / (0.5 * f->zoom * f->h) + f->off_y;
	if (mousecode == 2)
	{
		f->off_x = m_re;
		f->off_y = m_im;
		ft_render(f);
		return (0);
	}
	if (mousecode == 4)
		zoomer = 1.1;
	else if (mousecode == 5)
		zoomer = 1.0 / 1.1;
	else
		return (0);
	f->zoom *= zoomer;
	f->off_x = m_re - 2 * (x - f->w / 2.0) / (0.5 * f->zoom * f->w);
	f->off_y = m_im - (y - f->h / 2.0) / (0.5 * f->zoom * f->h);
	ft_render(f);
	return (0);
}
