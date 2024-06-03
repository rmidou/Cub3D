/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jde-meo <jde-meo@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:54:22 by jde-meo           #+#    #+#             */
/*   Updated: 2024/06/03 13:58:41 by jde-meo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	max(int i1, int i2)
{
	if (i1 > i2)
		return (i1);
	return (i2);
}

void	print_map(t_map *map)
{
	int	i;

	i = -1;
	while (map->map[++i])
		ft_printf("|%s|\n", map->map[i]);
}

void	error_list(int err, char *line)
{
	if (err == ERR_ALREADY_LOADED)
		printf("This texture is already loaded:\n%s\n", line);
	if (err == ERR_MISSING_CLR)
		printf("Missing color definition\n");
	if (err == ERR_MISSING_TEX)
		printf("Missing texture declaration\n");
	if (err == ERR_PARSING)
		printf("Parsing error on line:\n%s\n", line);
	if (err == ERR_MAP_OPEN)
		printf("Map needs to be closed\n");
	if (err == ERR_ARG)
		printf("Invalid argument list\n");
}

int	throw_error(int err, char *line)
{
	if (err == OKAY_OKAY)
		return (0);
	printf("Error\n");
	if (err == ERR_OPEN)
		printf("Failed to open file:\n%s\n", line);
	if (err == ERR_EXT)
		printf("Expected .cub file\n");
	if (err == ERR_MAP)
		printf("Map is invalid\n");
	if (err == ERR_NOFILE)
		printf("Expected filepath after identifier:\n%s\n", line);
	if (err == ERR_LOADTEX)
		printf("Failed to load texture:\n%s\n", line);
	if (err == ERR_NOCLR)
		printf("Expected color:\n%s\n", line);
	if (err == ERR_SYNTAX)
		printf("Syntax error:\n%s\n", line);
	if (err == ERR_NO_DATA_EXPECTED)
		printf("No data expected after map:\n%s\n", line);
	if (err == ERR_UNKNOWN)
		printf("Unkown identifier:\n%s\n", line);
	if (err == ERR_OUT_OF_BOUNDS)
		printf("Color data must be contained within [0-255]:\n%s\n", line);
	error_list(err, line);
	return (1);
}
