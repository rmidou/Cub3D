/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmidou <rmidou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:48:11 by rmidou            #+#    #+#             */
/*   Updated: 2024/05/24 15:08:18 by rmidou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <fcntl.h>
# include <math.h>

#define RED_PIXEL 0xFF0000
#define BLACK_PIXEL 0x000000
#define WHITE_PIXEL 0xFFFFFF

typedef struct s_main
{
	int		x;
	int		y;
	int		px;
	int		py;
	float		pa;
	float		dx;
	float		dy;
	float		fd;
	int		widhtmap;
	int		heightmap;
	
	char	**map;
	char	**buf;

	void	*mlxptr;
	void	*winptr;
	void	*black;
	void	*white;
	void	*bigblack;

}	t_main;

/*		main.c	*/
int		on_destroy(t_main *map);

/*		move.c	*/
float	deg_to_rad(int a);
int		move(int key, t_main *map);
int		fix_ang(int a);

/*		map.c	*/
void	free_map(t_main *map);
void	print_map(t_main *map);
int		read_map(t_main *map, char *av);

/*		img.c	*/
void	init_img(t_main *map);
void	put_(t_main *map);
void	put_img(char chara, t_main map);

/*		draw_rays.c	*/
void	draw_rays(t_main *map);
int		draw_line(t_main *main, int x0, int y0, int x1, int y1, int color);
void    draw_view_line(t_main *main);
#endif
