/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:09:53 by aeleimat          #+#    #+#             */
/*   Updated: 2025/01/01 09:07:43 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	exit_error(int fd, char *line)
{
	close(fd);
	free(line);
	write(2, "the map shape is wrong\n", 23);
	exit(1);
}

void	map_rectangular(char *av)
{
	int		fd;
	int		length;
	int		length2;
	char	*line;

	fd = open(av, O_RDONLY);
	line = get_next_line(fd);
	length = ft_strlen(line);
	free(line);
	line = get_next_line(fd);
	while (line)
	{
		length2 = ft_strlen(line);
		if (length != length2)
			exit_error(fd, line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}

void	process_lines_e_p_c(int fd, int length, t_collectibles *co)
{
	int		i;
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		while (i < length - 1)
		{
			if (line[i] == 'E')
				co->e_count++;
			else if (line[i] == 'P')
				co->p_count++;
			else if (line[i] == 'C')
				co->c_count ++;
			else if (!ft_strchr("EPCD01", line[i]))
				co->o_count++;
			i++;
		}
		free(line);
		line = get_next_line(fd);
	}
}

void	count_e_p_c(char *av)
{
	int				fd;
	int				length;
	char			*line;
	t_collectibles	co;

	co.e_count = 0;
	co.p_count = 0;
	co.c_count = 0;
	co.o_count = 0;
	fd = open(av, O_RDONLY);
	line = get_next_line(fd);
	length = ft_strlen(line);
	free(line);
	process_lines_e_p_c(fd, length, &co);
	close(fd);
	if (co.e_count != 1 || co.p_count != 1 || co.c_count < 1 || co.o_count)
	{
		write (2, "Error: only one 'E',one 'P', at least one 'C'\n", 47);
		exit (1);
	}
}
