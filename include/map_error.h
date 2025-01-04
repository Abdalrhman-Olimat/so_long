/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:25:51 by aeleimat          #+#    #+#             */
/*   Updated: 2025/01/04 04:02:06 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MAP_ERROR_H
# define MAP_ERROR_H
# include "so_long.h"

typedef struct s_collectibles
{
	int	e_count;
	int	p_count;
	int	c_count;
	int	o_count;
}	t_collectibles;
void	check_up_wall(char *line, int length, int *flag);
void	map_wall_side(char *line, int length, int *flag);
void	map_wall_bottom(char *line, int length, int *flag);
void	process_lines(int fd, int length, int *flag);
void	map_wall_main(char *av);
void	map_rectangular(char *av);
void	process_lines_e_p_c(int fd, int length, t_collectibles *collectibles);
void	count_e_p_c(char *av);
/************flood_file************/
int		check_path(t_map *data);
void	flood_fill(t_map *mp, char **map_copy);
void	free_map(char **map, int height);
char	**copy_map(char **map, int height);
int		load_map(char *filename, t_map *data);
//int load_map2(char *filename, t_game *game);
# endif