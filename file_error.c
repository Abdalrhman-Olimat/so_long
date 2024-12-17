/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:02:44 by aeleimat          #+#    #+#             */
/*   Updated: 2024/12/17 17:45:52 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "include/so_long.h"

void	cheack_name(char *av)
{
	int	fd;
	int	length;
	int	j;
	char		*bar;

	fd = open(av, O_RDONLY);
	close(fd);
	if (fd < 0)
	{
		write(2, "Error file doesn't open or doesn't exist\n", 41);
		exit(1);
	}
	length = ft_strlen(av);
	bar = ".bar";
	j = 4;
	while (j > 0)
	{
		if (av[length--] != bar[j--])
		{
			write(2, "Not a .bar file\n", 16);
			exit(1);
		}
	}
}

void	cheack_empty(char *av)
{
	int	fd;
	int	byte_read;
	char			*buffer;

	fd = open(av, O_RDONLY);
	buffer = malloc(sizeof(char));
	byte_read = read(fd, buffer, 1);
	free(buffer);
	close(fd);
	if (byte_read < 1)
	{
		write(2, "File is empty\n", 14);
		exit(1);
	}
}