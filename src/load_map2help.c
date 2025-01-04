/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map2help.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 03:46:41 by aeleimat          #+#    #+#             */
/*   Updated: 2025/01/04 03:47:05 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	enemy_pos(t_game *game, int x, int y)
{
	game->enemies[game->num_enemies].x = x;
	game->enemies[game->num_enemies].y = y;
	game->num_enemies++;
}

void	player_pos(t_game *game, int x, int y)
{
	game->map.player_x = x;
	game->map.player_y = y;
}

int	scan_map_for_obj(t_game *game)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
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

int	process_line2(t_game *game, char *line)
{
	int	len;

	len = ft_strlen2(line);
	if (len > 0 && line[len - 1] == '\n')
	{
		line[len - 1] = '\0';
		len--;
	}
	game->map.width = len;
	return (len);
}

int	process_line3(char *line)
{
	int	len;

	len = ft_strlen2(line);
	if (len > 0 && line[len - 1] == '\n')
	{
		line[len - 1] = '\0';
		len--;
	}
	return (len);
}
