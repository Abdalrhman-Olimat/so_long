/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 07:05:09 by aeleimat          #+#    #+#             */
/*   Updated: 2025/01/01 07:41:18 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

char	**copy_map(char **map, int height)
{
	int		i;
	char	**copy;

	copy = malloc(sizeof(char *) * (height + 1));
	i = 0;
	while (i < height)
	{
		copy[i] = ft_strdup(map[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	free_map(char **map, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

static	void	flood_fill_loop(t_map *mp, int x, int y)
{
	if (mp->map[x][y] == '1' || mp->map[x][y] == 'F')
		return ;
	if (mp->map[x][y] == 'C')
		mp->collectibles--;
	if (mp->map[x][y] == 'E')
		mp->exit_found = 1;
	mp->map[x][y] = 'F';
	if (x > 0)
		flood_fill_loop(mp, x - 1, y);
	if (x < mp->height - 1)
		flood_fill_loop(mp, x + 1, y);
	if (y > 0)
		flood_fill_loop(mp, x, y - 1);
	if (y < mp->width - 1)
		flood_fill_loop(mp, x, y + 1);
}

void	flood_fill(t_map *mp, char **map_copy)
{
	t_map	tmp;

	tmp = *mp;
	tmp.map = map_copy;
	flood_fill_loop(&tmp, tmp.player_x, tmp.player_y);
	mp->collectibles = tmp.collectibles;
	mp->exit_found = tmp.exit_found;
}

int	check_path(t_map *data)
{
	char	**map_copy;

	map_copy = copy_map(data->map, data->height);
	flood_fill(data, map_copy);
	free_map(map_copy, data->height);
	if (data->collectibles == 0 && data->exit_found)
		return (1);
	write(2, "Map is invalid: unreachable collectibles or exit\n", 49);
	return (0);
}
