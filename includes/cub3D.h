/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:55:18 by jde-meo           #+#    #+#             */
/*   Updated: 2024/06/03 14:00:39 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx/mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <math.h>

# define RED_PIXEL	0xFF0000
# define BLACK_PIXEL 0x000000
# define WHITE_PIXEL 0xFFFFFF
# define BLUE_PIXEL	0x77B5FE
# define PI			3.141592f
# define OFFSET		-0.f

# define CEIL	0
# define FLOOR	1
# define X_		0
# define Y_		1

# define HIT_N	0
# define HIT_S	1
# define HIT_E	2
# define HIT_W	3
# define HIT_D	4

# define MAP_CHARS	" 10NSEWD"

# define LN_TYPE_EMPTY		0
# define LN_TYPE_TXR		1
# define LN_TYPE_CLR		2
# define LN_TYPE_MAP		3
# define LN_TYPE_UNDEF		4

# define OKAY_OKAY				0
# define ERR_OPEN				1
# define ERR_NOFILE				2
# define ERR_LOADTEX			3
# define ERR_NOCLR				4
# define ERR_SYNTAX				5
# define ERR_NO_DATA_EXPECTED	6
# define ERR_UNKNOWN			7
# define ERR_OUT_OF_BOUNDS		8
# define ERR_PARSING			9
# define ERR_ARG				10
# define ERR_MAP_OPEN			11
# define ERR_MISSING_TEX		12
# define ERR_ALREADY_LOADED		13
# define ERR_MAP				14
# define ERR_MISSING_CLR		15
# define ERR_EXT				16

# define STAGE_DATA	0
# define STAGE_MAP	1
# define STAGE_DONE	2

# define SCREEN_W		1920.f
# define SCREEN_H		1080.f
# define FOV 			90.f
# define RENDER_DIST	8.f
# define SCREEN_DIST	.001f
# define COL_W			1
# define SPEED			0.25f
# define SCREEN_SIZE	64.f

# define COLLISION_DIST	0.6f

# define MOUSE			0
# define MOUSE_SPEED	2.5f
# define NB_FRAME		5

typedef struct s_veci
{
	int	x;
	int	y;
}	t_veci;

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

typedef struct s_anim
{
	t_txr	*txrs;
	int		size;
	int		frame;
}	t_anim;

typedef struct s_vecf
{
	float	x;
	float	y;
}	t_vecf;

typedef struct s_clr
{
	int	r;
	int	g;
	int	b;
	int	color_i;
}	t_clr;

typedef struct s_map
{
	char	*file;
	char	*data;
	char	**map;
	t_veci	size;
	t_veci	spawn;
	float	view;
	int		door;
	t_anim	n;
	t_anim	s;
	t_anim	e;
	t_anim	w;
	t_anim	d;
	t_clr	floor;
	t_clr	ceiling;
}	t_map;

typedef struct s_ray
{
	int		index;
	int		hit;
	float	a;
	t_vecf	p;
	t_vecf	d;
	t_vecf	n;
	t_vecf	dx;
	t_vecf	dy;
}	t_ray;

typedef struct s_main
{
	t_ray	plr;

	t_ray	ray;

	t_veci	mouse;

	t_map	map;

	t_txr	scr;

	int		update;

	void	*mlxptr;
	void	*winptr;
}	t_main;

/*		main.c			*/
int		on_destroy(t_main *map);

/*		move.c			*/
int		move(int key, t_main *map);
int		rgb(int t, int r, int g, int b);

/*		map.c			*/
void	free_main(t_main *main);
char	get_block2(t_main *main, t_vecf p);
void	free_map(void *mlxptr, t_map *m);

/*		img.c			*/
void	draw_line(t_main *main, t_veci start, t_veci end, int color);
void	reset_screen(t_main *main);
t_clr	get_pixel(t_txr t, int x, int y);
void	set_pixel(int color, t_txr t, int x, int y);
float	get_shade(int y);

/*		draw_rays.c		*/
void	draw_rays(t_main *map);
void	draw_line(t_main *main, t_veci start, t_veci end, int color);
void	shoot_rays(t_main *main);
char	get_block(t_main *main);

/*		textures.c		*/
void	draw_texture(t_main *m, int x_pos);
float	add_dithering(float l, int x, int y);
t_txr	get_hit_texture(t_main *m, t_ray r);
void	draw_row(t_main *m, t_veci p, t_txr t, float len);

/*		parsing.c		*/
int		build_map(void *mlx_ptr, t_map *m, char *file, t_main *main);
void	get_map_specs(t_map *m, t_main *main);

/*		parsing2.c		*/
int		read_mapline(t_map *m, char *line);
int		read_color_data(t_clr *c, char *line);
int		read_color(t_map *m, char *line);
int		read_texture(void *mlx_ptr, t_map *m, char *line);
int		load_tex(void *mlx_ptr, t_txr *t);

/*		error.c			*/
int		max(int i1, int i2);
int		throw_error(int err, char *line);
void	print_map(t_map *map);

/*		ray.c			*/
void	whey(t_ray *ray);
float	dist(t_vecf v);
void	init_dir(t_ray *r);
void	init_dir2(t_ray *r);

/*		minimap.c		*/
void	mini_map(t_main *main);

/*		color.c			*/
t_clr	color(int r, int g, int b);
t_clr	get_hit_color(t_main *m, t_ray r);
t_clr	scale_clr(t_clr c, float f);

/*		angles.c		*/
t_vecf	ang_to_vecf(float a);
float	fix_ang(float a);
float	to_rad(float a);
float	to_deg(float a);
t_vecf	rotate(t_vecf v, float a);

/*		vectors.c		*/
t_vecf	vecf(float x, float y);
float	dist(t_vecf v);
t_vecf	norm(t_vecf v);
t_vecf	add(t_vecf u, t_vecf v);
t_vecf	sub(t_vecf u, t_vecf v);

/*		vectors2.c		*/
t_vecf	scale(t_vecf v, float f);
int		get_line_height(t_main *m);
float	absf(float f);

/*		collisions.c	*/
void	clip_x(t_main *m, t_vecf block, char c, int stop);
void	clip_y(t_main *m, t_vecf block, char c, int stop);
void	check_collision(t_main *m);

/*		mouse.c			*/
void	update_mouse(t_main *main);
int		mouse(int x, int y, t_main *main);

/*		animation.c		*/
int		init_animation(t_anim *t, int frames);
void	init_texture(t_main *m);
void	update_textures(t_anim *t);
void	door_remove(t_main *m);

/*		flood_fill.c	*/
int		flood_fill(t_map *m, t_main *main);
int		verif_spawn(t_map *m);

/*		verif_map.c		*/
int		verif_color_line(t_clr *c, char *line);
int		verif_data(t_map *m);

#endif
