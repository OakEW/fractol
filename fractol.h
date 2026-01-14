/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ywang2 <ywang2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:54:03 by ywang2            #+#    #+#             */
/*   Updated: 2026/01/14 17:25:56 by ywang2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "minilibx-linux/mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <math.h>

typedef struct s_data
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	double			zoom;
	int				w;
	int				h;
	double			ix;
	double			iy;
	double			re;
	double			im;
	unsigned int	palette[256];
	int				set;
	int				max_iter;
	double			off_x;
	double			off_y;
	double			shift;
	int				animate;
	int				palette_set;
}	t_data;

double	ft_atof(const char *nptr);
int		is_valid(char *nptr);
int		check_arg(int argc, char **argv);
int		ft_strcmp(const char *s1, const char *s2);
void	clean_up(t_data *fractol);

int		animate(void *param);
void	rainbow_palette(t_data *fractol);
void	color_pix(t_data *fractol, int x, int y, int iteration);
void	ft_render(t_data *fractol);

void	mapping(t_data *fractol, int x, int y);
void	make_julia(t_data *fractol, int x, int y);
void	make_mandelbrot(t_data *fractol, int x, int y);
void	make_multibrot4(t_data *fractol, int x, int y);

int		close_x(t_data *fractol);
int		key_do_1(int key, t_data *fractol);
int		key_do_2(int key, t_data *fractol);
int		key_do_all(int key, t_data *fractol);
int		mouse_do(int mousecode, int x, int y, t_data *f);

t_data	init_all(char **argv);

#endif