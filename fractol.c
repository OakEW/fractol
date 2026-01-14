/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywang2 <ywang2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:53:54 by ywang2            #+#    #+#             */
/*   Updated: 2026/01/14 16:06:39 by ywang2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	close_x(t_data *fractol)
{
	mlx_loop_end(fractol->mlx);
	return (0);
}

int	key_do(int key, t_data *fractol)
{
	if (key == 65307)
		mlx_loop_end(fractol->mlx);
	if (key == 115)
		fractol->animate *= -1;
	if (key == 119)
		fractol->palette_set *= -1;
	if (key == 97 || key == 100)
	{
		fractol->shift += 0.1;
		if (key == 97)
			fractol->shift -= 0.2;
		rainbow_palette(fractol);
	}
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

t_data	init_all(char **argv)
{
	t_data	fractol;

	fractol.ix = 0.0;
	fractol.iy = 0.0;
	fractol.re = 0.0;
	fractol.im = 0.0;
	fractol.zoom = 1.0;
	fractol.w = 1200;
	fractol.h = 600;
	fractol.set = 2;
	fractol.off_x = 0.0;
	fractol.off_y = 0.0;
	fractol.max_iter = 100;
	fractol.shift = 1.3;
	fractol.animate = 1;
	fractol.palette_set = 1;
	fractol.mlx = mlx_init();
	fractol.win = mlx_new_window(fractol.mlx, fractol.w, fractol.h, argv[1]);
	fractol.img = mlx_new_image(fractol.mlx, fractol.w, fractol.h);
	fractol.addr = mlx_get_data_addr(fractol.img, &fractol.bits_per_pixel,
			&fractol.line_length, &fractol.endian);
	rainbow_palette(&fractol);
	return (fractol);
}

int	main(int argc, char **argv)
{
	t_data	fractol;

	if (check_arg(argc, argv) == 0)
		exit (1);
	fractol = init_all(argv);
	if (argc == 4)
	{
		fractol.ix = ft_atof(argv[2]);
		fractol.iy = ft_atof(argv[3]);
	}
	if (ft_strcmp(argv[1], "mandelbrot") == 0)
		fractol.set = 1;
	if (ft_strcmp(argv[1], "multibrot4") == 0)
		fractol.set = 3;
	ft_render(&fractol);
	mlx_hook(fractol.win, 17, 0, close_x, &fractol);
	mlx_hook(fractol.win, 2, 1L << 0, key_do, &fractol);
	mlx_hook(fractol.win, 4, 1L << 2, mouse_do, &fractol);
	mlx_loop_hook(fractol.mlx, animate, &fractol);
	mlx_loop(fractol.mlx);
	clean_up(&fractol);
}
