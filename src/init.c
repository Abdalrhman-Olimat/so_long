/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 11:18:12 by aeleimat          #+#    #+#             */
/*   Updated: 2025/01/03 17:15:13 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	init_game(t_game *game)
{
	int	win_width;
	int	win_height;

	game->mlx = mlx_init();
	if (!game->mlx)
	{
		write(2, "Error initializing MLX\n", 23);
		exit(1);
	}
	game->move_count = 0;
	game->current_frame = 0;
	game->frame_counter = 0;
	win_width = game->map.width * TILE_SIZE;
	win_height = game->map.height * TILE_SIZE;
	game->win = mlx_new_window(game->mlx, win_width, win_height, "so_long");
	if (!game->win)
	{
		write(2, "Error creating window\n", 22);
		exit(1);
	}
}

void	init_c(t_game *game, int img_w, int img_h, char *c_p[])
{
	int	i;

	i = 0;
	while (i < NUM_COLLECTIBLE_FRAMES)
	{
		game->img_coll[i] = mlx_xpm_file_to_image(game->mlx, c_p[i], &img_w, &img_h);
		if (!game->img_coll[i])
		{
			write(2, "Error loading collectible images\n", 33);
			exit(1);
		}
		i++;
	}
}

void	init_images(t_game *game)
{
	int		img_width;
	int		img_height;
	char	*collectible_paths[NUM_COLLECTIBLE_FRAMES] =
	{
		"image/collectible/gold2.xpm",
		"image/collectible/gold3.xpm",
		"image/collectible/gold4.xpm",
		"image/collectible/gold5.xpm",
		"image/collectible/gold6.xpm",
		"image/collectible/gold7.xpm"
	};
	game->img_wall = mlx_xpm_file_to_image(game->mlx, "image/wall.xpm", &img_width, &img_height);
	game->img_floor = mlx_xpm_file_to_image(game->mlx, "image/floor.xpm", &img_width, &img_height);
	game->img_player = mlx_xpm_file_to_image(game->mlx, "image/player.xpm", &img_width, &img_height);
	game->img_exit = mlx_xpm_file_to_image(game->mlx, "image/exit.xpm", &img_width, &img_height);
	game->img_ene = mlx_xpm_file_to_image(game->mlx, "image/enemy.xpm", &img_width, &img_height);
	init_c(game, img_width, img_height, collectible_paths);
	if (!game->img_wall || !game->img_floor || !game->img_player || !game->img_exit || !game->img_ene)
	{
		write(2, "Error loading images\n", 21);
		exit(1);
	}
}

// Render the map and objects
void	draw_map(t_game *game, int x, int y, int screen_x, int screen_y)
{
	mlx_put_image_to_window(game->mlx, game->win, game->img_floor, screen_x, screen_y);
	if (game->map.map[y][x] == '1')
		mlx_put_image_to_window(game->mlx, game->win, game->img_wall, screen_x, screen_y);
	if (game->map.map[y][x] == 'C')
		mlx_put_image_to_window(game->mlx, game->win, game->img_coll[game->current_frame], screen_x, screen_y);
	if (game->map.map[y][x] == 'E')
		mlx_put_image_to_window(game->mlx, game->win, game->img_exit, screen_x, screen_y);
	if (game->map.map[y][x] == 'P')
		mlx_put_image_to_window(game->mlx, game->win, game->img_player, screen_x, screen_y);
}
void	draw_enemies(t_game *game)
{
	int i;
	
	i = 0;
	while (i < game->num_enemies)
	{
		//screen
		int	s_x;
		int	s_y;

		s_x = game->enemies[i].x * TILE_SIZE;
		s_y = game->enemies[i].y * TILE_SIZE;
		mlx_put_image_to_window(game->mlx, game->win, game->img_ene, s_x, s_y);
		i++;
	}
}
