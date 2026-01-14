/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywang2 <ywang2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:53:54 by ywang2            #+#    #+#             */
/*   Updated: 2026/01/14 18:59:10 by ywang2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywang2 <ywang2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:53:54 by ywang2            #+#    #+#             */
/*   Updated: 2026/01/14 23:48:05 by ywang2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_help(t_data *fractol)
{
	fractol->w = 1200;
	fractol->h = 600;
	fractol->ix = 0.0;
	fractol->iy = 0.0;
	fractol->re = 0.0;
	fractol->im = 0.0;
	fractol->zoom = 1.0;
	fractol->set = 2;
	fractol->off_x = 0.0;
	fractol->off_y = 0.0;
	fractol->max_iter = 100;
	fractol->shift = 1.3;
	fractol->animate = 1;
	fractol->palette_set = 1;
	fractol->color_index = malloc(sizeof(int) * fractol->w * fractol->h);
	if (!fractol->color_index)
		handle_errors(fractol);
}

void	handle_errors(t_data *fractol)
{
	clean_up(fractol);
	exit (1);
}

t_data	init_all(char **argv)
{
	t_data	fractol;

	init_help(&fractol);
	fractol.mlx = mlx_init();
	if (!fractol.mlx)
		handle_errors(&fractol);
	fractol.win = mlx_new_window(fractol.mlx, fractol.w, fractol.h, argv[1]);
	if (!fractol.win)
		handle_errors(&fractol);
	fractol.img = mlx_new_image(fractol.mlx, fractol.w, fractol.h);
	if (!fractol.img)
		handle_errors(&fractol);
	fractol.addr = mlx_get_data_addr(fractol.img, &fractol.bits_per_pixel,
			&fractol.line_length, &fractol.endian);
	if (!fractol.addr)
		handle_errors(&fractol);
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
	mlx_hook(fractol.win, 2, 1L << 0, key_do_all, &fractol);
	mlx_hook(fractol.win, 4, 1L << 2, mouse_do, &fractol);
	mlx_loop_hook(fractol.mlx, animate, &fractol);
	mlx_loop(fractol.mlx);
	clean_up(&fractol);
}
