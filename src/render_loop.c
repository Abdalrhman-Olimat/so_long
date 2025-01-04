/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 11:28:22 by aeleimat          #+#    #+#             */
/*   Updated: 2025/01/04 03:00:34 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	render_map(t_game *game)
{
	int		x;
	int		y;
	int		i;
	char	*moves_str;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			game->screen_x = x * TILE_SIZE;
			game->screen_y = y * TILE_SIZE;
			draw_map(game, x, y);
			x++;
		}
		y++;
	}
	i = 0;
	draw_enemies(game);
	moves_str = ft_itoa(game->move_count);
	mlx_string_put(game->mlx, game->win, 10, 10, 0xFF0000, moves_str);
	free(moves_str);
}

int	handle_close(t_game *game)
{
	cleanup_game(game);
	exit(0);
	return (0);
}

int	game_loop(t_game *game)
{
	static int	enemy_move_counter = 0;

	game->frame_counter++;
	if (game->frame_counter >= FRAME_DELAY)
	{
		game->current_frame = (game->current_frame + 1) % NUM_C_FRAMES;
		game->frame_counter = 0;
	}
	enemy_move_counter++;
	if (enemy_move_counter >= ENEMY_MOVE_DELAY)
	{
		move_enemies(game);
		enemy_move_counter = 0;
	}
	render_map(game);
	return (0);
}
