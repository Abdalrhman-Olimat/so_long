/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 19:38:11 by aeleimat          #+#    #+#             */
/*   Updated: 2025/01/01 07:44:38 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	get_map_height(char *filename)
{
	int		fd;
	int		height;
	char	*line;

	height = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	while ((line = get_next_line(fd)) != NULL)
	{
		height++;
		free(line);
	}
	close(fd);
	return (height);
}

int	allocate_map(t_map *data)
{
	data->map = malloc(sizeof(char *) * (data->height + 1));
	if (!data->map)
		return (0);
	return (1);
}

int	process_line(char *line, int i, t_map *data, int *player_found)
{
	if (i == 0)
		data->width = ft_strlen(line) - 1;
	else if (ft_strlen(line) - 1 != data->width)
	{
		write(2, "Error: inconsistent map width\n", 30);
		return (0);
	}
	for (int j = 0; line[j] && line[j] != '\n'; j++)
	{
		if (line[j] == 'P')
		{
			data->player_x = i;
			data->player_y = j;
			(*player_found)++;
		}
		else if (line[j] == 'C')
			data->collectibles++;
	}
	return (1);
}

int	process_map_lines(char *filename, t_map *data)
{
	int		fd;
	int		i;
	int		player_found;
	char	*line;

	i = 0;
	player_found = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	while ((line = get_next_line(fd)) != NULL)
	{
		data->map[i] = line;
		if (!process_line(line, i, data, &player_found))
		{
			close(fd);
			return (0);
		}
		i++;
	}
	data->map[i] = NULL;
	close(fd);
	return (1);
}

int	load_map(char *filename, t_map *data)
{
	data->collectibles = 0;
	data->height = get_map_height(filename);
	if (data->height == 0)
		return (0);
	if (!allocate_map(data))
		return (0);
	if (!process_map_lines(filename, data))
		return (0);
	return (1);
}
