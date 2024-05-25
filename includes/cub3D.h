/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larz <larz@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:48:11 by rmidou            #+#    #+#             */
/*   Updated: 2024/05/25 17:10:24 by larz             ###   ########.fr       */
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
#define BLUE_PIXEL 0x77B5FE
#define PI			3.141592f

#define SCREEN_W = 640
#define SCREEN_H = 480
#define FOV = 90

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

	void	*img;
	char	*scr_data;
	int		bpp;
	int		line;
	int		endian;

	void	*mlxptr;
	void	*winptr;
	void	*black;
	void	*white;
	void	*blue;
	void	*little_black;
	void	*little_white;

}	t_main;

typedef struct s_veci
{
	int	x;
	int	y;
}	t_veci;

typedef struct s_vecf
{
	float	x;
	float	y;
}	t_vecf;

typedef struct s_txr
{
	char			*file;
	char			*data;
	void			*img;
	int				bpp;
	int				line;
	int				endian;
	t_veci			size;
}	t_txr;

typedef struct s_map
{
	char	*file;
	char	*data;
	t_veci	size;
	t_veci	spawn;
	float	view;
}	t_map;

/*		main.c	*/
int		on_destroy(t_main *map);

/*		move.c	*/
float	deg_to_rad(float a);
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
