/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:44:56 by aeleimat          #+#    #+#             */
/*   Updated: 2025/01/03 05:51:36 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"






/*
int load_map2(char *filename, t_game *game)
{
	int	fd;
	
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);

	game->map.height = 0;
	game->map.width = 0;
	game->map.map = NULL;

	while (1)
	{
		char *line = get_next_line(fd);
		if (!line)
			break;

		// Remove trailing newline
		int len = ft_strlen2(line);
		if (len > 0 && line[len - 1] == '\n')
		{
			line[len - 1] = '\0';
			len--;
		}
		// Track max width
		if (len > game->map.width)
			game->map.width = len;
		// Append new line to the map array
		char **tmp = malloc(sizeof(char *) * (game->map.height + 2));
		for (int i = 0; i < game->map.height; i++)
			tmp[i] = game->map.map[i];
		tmp[game->map.height] = line;
		tmp[game->map.height + 1] = NULL;

		free(game->map.map);
		game->map.map = tmp;
		game->map.height++;
	}
	close(fd);

	if (game->map.height == 0)
		return (0);

	// Initialize counters
	game->map.collectibles = 0;
	game->map.player_x = -1;
	game->map.player_y = -1;
	game->num_enemies = 0;

	// Scan map for objects
	for (int y = 0; y < game->map.height; y++)
	{
		for (int x = 0; x < game->map.width; x++)
		{
			char c = game->map.map[y][x];
			if (c == 'P')
			{
				game->map.player_x = x;
				game->map.player_y = y;
			}
			else if (c == 'C')
				game->map.collectibles++;
			else if (c == 'D' && game->num_enemies < MAX_ENEMIES)
			{
				game->enemies[game->num_enemies].x = x;
				game->enemies[game->num_enemies].y = y;
				game->num_enemies++;
			}
		}
	}
	return (1);
}
*/
void enemy_pos(t_game *game, int x, int y)
{
	game->enemies[game->num_enemies].x = x;
	game->enemies[game->num_enemies].y = y;
	game->num_enemies++;
}

void player_pos(t_game *game, int x, int y)
{
	game->map.player_x = x;
	game->map.player_y = y;
}

int scan_map_for_obj(t_game *game)
{
	int y;
	
	y = 0;
	while (y < game->map.height)
	{
		int x;

		x = 0;
		while (x < game->map.width)
		{
			char c;

			c = game->map.map[y][x];
			if (c == 'P')
				player_pos(game, x, y);
			else if (c == 'C')
				game->map.collectibles++;
			else if (c == 'D' && game->num_enemies < MAX_ENEMIES)
				enemy_pos(game, x, y);
			x++;
		}
		y++;
	}
	return (1);
}

int load_map2(char *filename, t_game *game)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);

	// Read the first line to set the width
	char *line = get_next_line(fd);
	if (line)
	{
		int len = ft_strlen2(line);
		if (len > 0 && line[len - 1] == '\n')
		{
			line[len - 1] = '\0';
			len--;
		}
		game->map.width = len; // Set the width based on the first line
	}

	// Read the rest of the lines
	while (line)
	{
		// Append new line to the map array
		char **tmp = malloc(sizeof(char *) * (game->map.height + 2));
		int i = 0;
		while (i < game->map.height)
		{
			tmp[i] = game->map.map[i];
			i++;
		}
		tmp[game->map.height] = line;
		tmp[game->map.height + 1] = NULL;
		free(game->map.map);
		game->map.map = tmp;
		game->map.height++;

		// Read the next line
		line = get_next_line(fd);
		if (line)
		{
			int len = ft_strlen2(line);
			if (len > 0 && line[len - 1] == '\n')
			{
				line[len - 1] = '\0';
				len--;
			}
		}
	}
	close(fd);
	if (game->map.height == 0)
		return (0);
	scan_map_for_obj(game);

	return (1);
}



void error_handel(char *av, t_map *data)
{
	int i;
	
	cheack_name(av);
	cheack_empty(av);
	map_rectangular(av);
	map_wall_main(av);
	count_e_p_c(av);
	if (!load_map(av, data))
	{
		write(2, "Error loading map\n", 18);
		exit (1);
	}
	i = check_path(data);
	free_map(data->map, data->height);
	if (i == 0)
		exit (1);
}

int main(int ac, char **av)
{
	t_game  game;
	t_map   data;

	if (ac != 2)
	{
		write(2, "Usage: ./so_long <map_file>\n", 28);
		return (1);
	}
	error_handel(av[1], &data);
	ft_memset(&game, 0, sizeof(t_game));
	ft_memset(&game.map, 0, sizeof(t_map));
	if (!load_map2(av[1], &game))
	{
		write(2, "Error loading map\n", 18);
		return (1);
	}
	init_game(&game);
	init_images(&game);
	render_map(&game);
	mlx_hook(game.win, ClientMessage, StructureNotifyMask, handle_close, &game);
	mlx_hook(game.win, KeyPress, KeyPressMask, handle_keypress, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	cleanup_game(&game);
	return (0);
}
