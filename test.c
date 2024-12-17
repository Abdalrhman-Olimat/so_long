/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:44:56 by aeleimat          #+#    #+#             */
/*   Updated: 2024/12/17 18:01:26 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/so_long.h"

void error_handel(char *av)
{
	cheack_name(av);
	cheack_empty(av);
	map_rectangular(av);
	map_wall_main(av);
	count_e_p_c(av);
	

}

int	main(int ac,char **av)
{
	if (ac != 2)
	{
		write(2, "Error1\n", 7);
		return (0);
	}
	error_handel(av[1]);
}
