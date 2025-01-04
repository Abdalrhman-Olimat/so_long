/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:44:56 by aeleimat          #+#    #+#             */
/*   Updated: 2025/01/04 03:46:03 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	append_line_to_map(t_game *game, char *line)
{
	int		i;
	char	**tmp;

	tmp = malloc(sizeof(char *) * (game->map.height + 2));
	i = 0;
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
}

int	load_map2(char *filename, t_game *game)
{
	int		fd;
	int		len;
	int		i;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	if (line)
		len = process_line2(game, line);
	while (line)
	{
		append_line_to_map(game, line);
		line = get_next_line(fd);
		if (line)
			len = process_line3(line);
	}
	close(fd);
	if (game->map.height == 0)
		return (0);
	scan_map_for_obj(game);
	return (1);
}

void	error_handel(char *av, t_map *data)
{
	int	i;

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

int	main(int ac, char **av)
{
	t_game	game;
	t_map	data;

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
