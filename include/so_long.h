/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 03:57:12 by aeleimat          #+#    #+#             */
/*   Updated: 2025/01/04 04:31:48 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# define TILE_SIZE 65
# define NUM_C_FRAMES 6
# define FRAME_DELAY 33
# define ENEMY_MOVE_DELAY 70
# define MAX_ENEMIES 10000

# include "struct.h"
# include "file_error.h"
# include "map_error.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../mlx_linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include "../Libft/libft.h"

void	init_game(t_game *game);
void	init_images(t_game *game);
void	render_map(t_game *game);
void	cleanup_game(t_game *game);
int		handle_keypress(int keysym, t_game *game);
int		handle_close(t_game *game);
int		game_loop(t_game *game);
void	move_player(t_game *game, int dx, int dy, int i);
void	move_enemies(t_game *game);
int		load_map2(char *filename, t_game *game);
int		check_path(t_map *data);
void	free_map(char **map, int height);
char	*ft_strjoin2(char *s1, char *s2);
int		ft_strlen2(char *str);
char	*check_for_newline(char *str);
char	*get_next_line(int fd);

/**********************init **************/
void	init_game(t_game *game);
void	init_c(t_game *game, int img_width, int img_height,
			char *collectible_paths[]);
void	init_images(t_game *game);
void	draw_map(t_game *game, int x, int y);
void	draw_enemies(t_game *game);
/**********************movement **************/
int		is_valid_enemy_move(t_game *game, int new_x,
			int new_y, int enemy_index);
void	move_player(t_game *game, int dx, int dy, int i);
int		move_player_help(t_game *game, int new_x, int new_y);
void	print_on_terminal(t_game *game);
int		handle_keypress(int keysym, t_game *game);
/***************enemie ******************/
void	calculate_enemy_move(int *dx, int *dy);
void	move_enemies(t_game *game);
/**************render*******************/
int		game_loop(t_game *game);
int		handle_close(t_game *game);
void	render_map(t_game *game);
/**************load_map2help*******************/
int		process_line3(char *line);
int		process_line2(t_game *game, char *line);
int		scan_map_for_obj(t_game *game);
void	player_pos(t_game *game, int x, int y);
void	enemy_pos(t_game *game, int x, int y);

#endif