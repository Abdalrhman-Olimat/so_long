/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 05:44:35 by aeleimat          #+#    #+#             */
/*   Updated: 2025/01/03 17:08:50 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

// Clean up resources
void	cleanup_game_help1(t_game *game)
{
	if (game->img_wall)
	{
		mlx_destroy_image(game->mlx, game->img_wall);
		game->img_wall = NULL;
	}
	if (game->img_floor)
	{
		mlx_destroy_image(game->mlx, game->img_floor);
		game->img_floor = NULL;
	}
	if (game->img_player)
	{
		mlx_destroy_image(game->mlx, game->img_player);
		game->img_player = NULL;
	}
	if (game->img_exit)
	{
		mlx_destroy_image(game->mlx, game->img_exit);
		game->img_exit = NULL;
	}
}

void	cleanup_game_help2(t_game *game)
{
	if (game->img_ene)
	{
		mlx_destroy_image(game->mlx, game->img_ene);
		game->img_ene = NULL;
	}
	if (game->win)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
	}
	if (game->mlx)
	{
		free(game->mlx);
		game->mlx = NULL;
	}
	if (game->map.map)
	{
		free_map(game->map.map, game->map.height);
		game->map.map = NULL;
	}
}

void	cleanup_game(t_game *game)
{
	int	i;

	i = 0;
	cleanup_game_help1(game);
	while (i < NUM_COLLECTIBLE_FRAMES)
	{
		if (game->img_coll[i])
		{
			mlx_destroy_image(game->mlx, game->img_coll[i]);
			game->img_coll[i] = NULL;
		}
		i++;
	}
	cleanup_game_help2(game);
}
