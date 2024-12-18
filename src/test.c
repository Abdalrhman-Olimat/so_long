/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:44:56 by aeleimat          #+#    #+#             */
/*   Updated: 2024/12/18 08:01:07 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"



void error_handel(char *av)
{
	cheack_name(av);
	cheack_empty(av);
	map_rectangular(av);
	map_wall_main(av);
	count_e_p_c(av);
	
}


int main(int ac, char **av)
{
    t_map data;

    if (ac != 2)
    {
        write(2, "Error1\n", 7);
        return (0);
    }
    error_handel(av[1]);

    if (!load_map(av[1], &data))
    {
        write(2, "Error loading map\n", 18);
        return (1);
    }

    if (check_path(data.map, data.height, data.width, data.player_x, data.player_y, data.collectibles))
        printf("Path is good\n");

    free_map(data.map, data.height);
    return (0);
}