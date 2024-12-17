/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:02:22 by aeleimat          #+#    #+#             */
/*   Updated: 2024/12/17 17:44:53 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"

void	check_up_wall(char *line, int length, int *flag)
{
	int	i;

	i = 0;
	while (i < length - 1)
	{
		if (line[i] != '1')
		{
			write(2, "up wall is wrong\n", 17);
			*flag = 1;
			break ;
		}
		i++;
	}
}


void	map_wall_side(char *line, int length, int *flag)
{
	if (line[0] != '1' || line[length - 2] != '1')
	{
		write(2, "side wall is wrong\n", 19);
		*flag = 1;
	}
}

void	map_wall_bottom(char *line, int length, int *flag)
{
	int	i;

	i = 0;
	while (i < length - 1)
	{
		if (line[i] != '1')
		{
			write(2, "bottom wall is wrong\n", 21);
			*flag = 1;
			break ;
		}
		i++;
	}
}

void    process_lines(int fd, int length, int *flag)
{
	char	*line;
	char	*last_line;

	line = NULL;
	last_line = NULL;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (last_line)
			free(last_line);
		last_line = line;
		map_wall_side(line, length, flag);
	}
	if (last_line)
	{
		map_wall_bottom(last_line, length, flag);
		free(last_line);
	}
}
void	map_wall_main(char *av)
{
	int	fd;
	int	flag;
	int	length;
	char		*line;

	flag = 0;
	fd = open(av, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
		exit(write(2, "Error reading file\n", 19));
	length = ft_strlen(line);
	check_up_wall(line, length, &flag);
	free(line);
	process_lines(fd, length, &flag);
	close(fd);
	if (flag)
		exit(0);
}