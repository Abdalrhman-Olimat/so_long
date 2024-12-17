/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:25:51 by aeleimat          #+#    #+#             */
/*   Updated: 2024/12/17 17:32:23 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MAP_ERROR_H
# define MAP_ERROR_H
# include "so_long.h"
void	check_up_wall(char *line, int length, int *flag);
void	map_wall_side(char *line, int length, int *flag);
void	map_wall_bottom(char *line, int length, int *flag);
void    process_lines(int fd, int length, int *flag);
void	map_wall_main(char *av);
void	map_rectangular(char *av);
void process_lines_e_s_c(int fd, int length, int *e, int *s, int *c, int *o);
void count_e_s_c(char *av);
# endif