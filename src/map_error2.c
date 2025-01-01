/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:09:53 by aeleimat          #+#    #+#             */
/*   Updated: 2024/12/30 13:24:06 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

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
	while ((line = get_next_line(fd)) != NULL)
	{
		length2 = ft_strlen(line);
		if (length != length2)
		{
			close(fd);
			free(line);
			write(2, "the map shape is wrong\n", 23);
			exit(1);
		}
		free(line);
	}
	free(line);
	close(fd);
}

void	process_lines_e_p_c(int fd, int length, int *e, int *p, int *c, int *o)
{
    int		i;
    char	*line;

    while ((line = get_next_line(fd)) != NULL)
    {
		i = 0;
		while (i < length - 1)
		{
			if (line[i] == 'E')
				(*e)++;
			else if (line[i] == 'P')
				(*p)++;
			else if (line[i] == 'C')
				(*c)++;
			else if (line[i] != 'E' && line[i] != 'P' && line[i] != 'C' && line[i] != 'D' && line[i] != '0' && line[i] != '1')
				(*o)++;
			i++;
		}
        free(line);
    }
}

void	count_e_p_c(char *av)
{
	int			fd;
	int			length;
	int			e_count;
	int			p_count;
	int			c_count;
	int			i;
	int			o_count;
	char		*line;

	e_count = 0;
	p_count = 0;
	c_count = 0;
	o_count = 0;
	fd = open(av,O_RDONLY);
	line = get_next_line(fd);
	length = ft_strlen(line);
	free(line);
	process_lines_e_p_c(fd, length, &e_count, &p_count, &c_count, &o_count);
	close(fd);
	if (e_count!= 1 || p_count!= 1 || c_count <= 0 || o_count != 0)
	{
		write (2,"Error: there should be exactly one 'E' and one 'p' and at least one 'C'and nothing else\n",87);
		exit (1);
	}
}
