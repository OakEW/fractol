/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywang2 <ywang2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:53:54 by ywang2            #+#    #+#             */
/*   Updated: 2026/01/13 15:12:44 by ywang2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	close_esc(int keycode, t_data *fractol)
{
	if (keycode == 65307)
		mlx_loop_end(fractol->mlx);
	return (0);
}

int	close_x(t_data *fractol)
{
	mlx_loop_end(fractol->mlx);
	return (0);
}

int	mouse_do(int mousecode, int x, int y, t_data *fractol)
{
	(void)x;
	(void)y;
	if (mousecode == 4 || mousecode == 5)
	{
		if (mousecode == 4)
			fractol->zoom *= 1.1;
		if (mousecode == 5)
			fractol->zoom /= 1.1;
		ft_render(fractol);
	}
	return (0);
}

t_data	init_all(char **argv)
{
	t_data	fractol;

	fractol.ix = 0.0;
	fractol.iy = 0.0;
	fractol.zoom = 1.0;
	fractol.w = 1200;
	fractol.h = 600;
	fractol.set = 2;
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
	ft_render(&fractol);
	mlx_hook(fractol.win, 17, 0, close_x, &fractol);
	mlx_hook(fractol.win, 2, 1L << 0, close_esc, &fractol);
	mlx_hook(fractol.win, 4, 1L << 2, mouse_do, &fractol);
	mlx_loop(fractol.mlx);
	clean_up(&fractol);
}
