/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 07:05:09 by aeleimat          #+#    #+#             */
/*   Updated: 2024/12/18 08:01:50 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

char	**copy_map(char **map, int height)
{
	int	i;
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

void	flood_fill(char **map, int x, int y, int *collectibles, int *exit_found)
{
	if (map[x][y] == '1' || map[x][y] == 'F')
		return;
	if (map[x][y] == 'C')
		(*collectibles)--;
	if (map[x][y] == 'E')
		*exit_found = 1;
	map[x][y] = 'F';
	if (x > 0)
		flood_fill(map, x - 1, y, collectibles, exit_found);
	if (map[x + 1])
		flood_fill(map, x + 1, y, collectibles, exit_found);
	if (y > 0)
		flood_fill(map, x, y - 1, collectibles, exit_found);
	if (map[x][y + 1])
		flood_fill(map, x, y + 1, collectibles, exit_found);
}

int check_path(char **map, int height, int width, int player_x, int player_y, int total_collectibles)
{
    int exit_found = 0;
    int collectibles = total_collectibles; // Initialize local collectibles
    char **map_copy;

    map_copy = copy_map(map, height);
    flood_fill(map_copy, player_x, player_y, &collectibles, &exit_found);
    free_map(map_copy, height);

    if (collectibles == 0 && exit_found)
        return (1);

    write(2, "Map is invalid: unreachable collectibles or exit\n", 49);
    return (0);
}