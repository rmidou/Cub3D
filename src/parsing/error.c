#include "../includes/cub3D.h"

int	throw_error(int err, char *line)
{
	if (err == OKAY_OKAY)
		return (0);
	ft_printf("Error\n");
	if (err == ERR_OPEN)
		ft_printf("Failed to open file:\n%s\n", line);
	if (err == ERR_NOFILE)
		ft_printf("Expected filepath after identifier:\n%s\n", line);
	if (err == ERR_LOADTEX)
		ft_printf("Failed to load texture:\n%s\n", line);
	if (err == ERR_NOCLR)
		ft_printf("Expected color:\n%s\n");
	if (err == ERR_SYNTAX)
		ft_printf("Syntax error:\n%s\n");
	if (err == ERR_NO_DATA_EXPECTED)
		ft_printf("No data expected after map:\n%s\n");
	if (err == ERR_UNKNOWN)
		ft_printf("Unkown identifier:\n%s\n", line);
	if (err == ERR_OUT_OF_BOUNDS)
		ft_printf("Color data must be contained within [0-255]:\n%s\n", line);
	return (1);
}
