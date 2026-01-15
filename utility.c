/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywang2 <ywang2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 15:00:41 by ywang2            #+#    #+#             */
/*   Updated: 2026/01/15 18:08:12 by ywang2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	ft_atof(const char *nptr)
{
	int		x;
	double	d;
	double	n;
	double	f;

	x = 1;
	d = 10.0;
	n = 0.0;
	f = 0.0;
	while (*nptr && (*nptr <= 32 || (*nptr >= 9 && *nptr <= 13)))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
		if (*nptr++ == '-')
			x *= -1.0;
	while (*nptr >= '0' && *nptr <= '9')
		n = n * 10 + (*nptr++ - 48);
	if (*nptr == '.')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		f += (*nptr++ - 48) / d;
		d *= 10.0;
	}
	return (x * (n + f));
}

int	is_valid(char *nptr)
{
	int	i;

	i = 0;
	while (*nptr && *nptr <= 32)
		nptr++;
	if (*nptr == '+' || *nptr == '-')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		nptr++;
		i++;
	}
	if (*nptr == '.')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		nptr++;
		i++;
	}
	while (*nptr && *nptr <= 32)
		nptr++;
	if (i == 0 || *nptr > 32)
		return (0);
	return (1);
}

int	check_arg(int argc, char **argv)
{
	if (argc < 2)
		return (write(2, "choose: mandelbrot, julia, multibrot4\n", 39), 0);
	if (ft_strcmp(argv[1], "mandelbrot") == 0
		|| ft_strcmp(argv[1], "multibrot4") == 0)
	{
		if (argc == 2)
			return (1);
		else
			return (write(2, "this set doesn't take extra arg\n", 33), 0);
	}
	else if (ft_strcmp(argv[1], "julia") == 0)
	{
		if (argc == 4 && is_valid(argv[2]) && is_valid(argv[3]))
			return (2);
		else
			return (write(2, "julia takes two arguments(floats)\n", 35), 0);
	}
	else
		return (write(2, "choose: mandelbrot, julia, multibrot4\n", 39), 0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void	clean_up(t_data *fractol)
{
	if (fractol->iter)
		free(fractol->iter);
	if (fractol->img)
		mlx_destroy_image(fractol->mlx, fractol->img);
	if (fractol->win)
		mlx_destroy_window(fractol->mlx, fractol->win);
	if (fractol->mlx)
	{
		mlx_destroy_display(fractol->mlx);
		free (fractol->mlx);
	}
}
