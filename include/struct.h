/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 04:31:08 by aeleimat          #+#    #+#             */
/*   Updated: 2025/01/04 04:33:24 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_map
{
	char	**map;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	int		collectibles;
	int		exit_found;
}	t_map;

typedef struct s_enemy
{
	int	x;
	int	y;
}	t_enemy;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_map	map;
	t_enemy	enemies[MAX_ENEMIES];
	int		num_enemies;
	void	*img_wall;
	void	*img_floor;
	void	*img_player;
	void	*img_exit;
	void	*img_coll[NUM_C_FRAMES];
	void	*img_ene;
	int		current_frame;
	int		frame_counter;
	int		move_count;
	int		screen_y;
	int		screen_x;
}	t_game;
#endif