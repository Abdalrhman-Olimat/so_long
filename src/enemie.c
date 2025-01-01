/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemie.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 11:26:05 by aeleimat          #+#    #+#             */
/*   Updated: 2025/01/01 11:26:19 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void calculate_enemy_move(int *dx, int *dy)
{
    int direction;
	
	direction = rand() % 4;
    *dx = 0;
    *dy = 0;
    if (direction == 0)
        *dx = 1;
    else if (direction == 1)
        *dx = -1;
    else if (direction == 2)
        *dy = 1;
    else if (direction == 3)
        *dy = -1;
}

void move_enemies(t_game *game)
{
    int i = 0;
    while (i < game->num_enemies)
    {
        int dx, dy;
        calculate_enemy_move(&dx, &dy);
        int new_x;
        int new_y;
		
		new_x = game->enemies[i].x + dx;
		new_y = game->enemies[i].y + dy;
        if (!is_valid_enemy_move(game, new_x, new_y, i))
        {
            i++;
            continue;
        }
        game->map.map[game->enemies[i].y][game->enemies[i].x] = '0';
        game->map.map[new_y][new_x] = 'D';
        game->enemies[i].x = new_x;
        game->enemies[i].y = new_y;

        i++;
    }
}