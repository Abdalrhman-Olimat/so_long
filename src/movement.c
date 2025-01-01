/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 11:22:17 by aeleimat          #+#    #+#             */
/*   Updated: 2025/01/01 11:22:41 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int handle_keypress(int keysym, t_game *game)
{
	int i;
	
	i = 0;
    if (keysym == XK_Escape)
    {
        cleanup_game(game);
        exit(0);
    }
    if (keysym == XK_w || keysym == XK_W || keysym == XK_Up)
        move_player(game, 0, -1, i);
    else if (keysym == XK_s || keysym == XK_S || keysym == XK_Down)
        move_player(game, 0, 1, i);
    else if (keysym == XK_a || keysym == XK_A || keysym == XK_Left)
        move_player(game, -1, 0, i);
    else if (keysym == XK_d || keysym == XK_D || keysym == XK_Right)
        move_player(game, 1, 0, i);
    return (0);
}
void print_on_terminal(t_game *game)
{
	char *move_str;
	
	move_str = ft_itoa(game->move_count);
	write(1, "Moves: ", 7);
	write(1, move_str, ft_strlen(move_str));
	write(1, "\n", 1);
	free(move_str);
}

// Move player function
int move_player_help(t_game *game, int new_x, int new_y)
{
	if (game->map.map[new_y][new_x] == '1')
        return 1;
    if (game->map.map[new_y][new_x] == 'E' && game->map.collectibles > 0)
    {
        write(1, "Collect all collectibles before exiting!\n", 41);
        return 1;
    }
    if (game->map.map[new_y][new_x] == 'E' && game->map.collectibles == 0)
    {
        write(1, "You win!\n", 9);
        cleanup_game(game);
        exit(0);
    }
    if (game->map.map[new_y][new_x] == 'C')
    {
        game->map.collectibles--;
        game->map.map[new_y][new_x] = '0';
    }
	return 0;
}

void move_player(t_game *game, int dx, int dy, int i)
{
    int new_x;
    int new_y;

    new_x = game->map.player_x + dx;
    new_y = game->map.player_y + dy;
    if (move_player_help(game, new_x, new_y))
        return;
    while (i < game->num_enemies)
    {
        if (new_x == game->enemies[i].x && new_y == game->enemies[i].y)
        {
            write(1, "You were caught by an enemy!\n", 29);
            cleanup_game(game);
            exit(0);
        }
        i++;
    }
    game->map.map[game->map.player_y][game->map.player_x] = '0';
    game->map.map[new_y][new_x] = 'P';
    game->map.player_x = new_x;
    game->map.player_y = new_y;
    game->move_count++;
    print_on_terminal(game);
    render_map(game);
}

int	is_valid_enemy_move(t_game *game, int new_x, int new_y, int enemy_index)
{
    if (new_x < 0 || new_x >= game->map.width ||
        new_y < 0 || new_y >= game->map.height)
        return 0;
    if (game->map.map[new_y][new_x] == '1' ||
        game->map.map[new_y][new_x] == 'C' ||
        game->map.map[new_y][new_x] == 'E')
        return 0;
    if (new_x == game->map.player_x && new_y == game->map.player_y)
    {
        write(1, "You were caught by an enemy!\n", 29);
        cleanup_game(game);
        exit(0);
    }
    int j;
	
	j = 0;
    while (j < game->num_enemies)
    {
        if (j != enemy_index && game->enemies[j].x == new_x && game->enemies[j].y == new_y)
            return 0;
        j++;
    }
    return 1;
}
