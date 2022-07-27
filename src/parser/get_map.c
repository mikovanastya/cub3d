/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 18:03:50 by majacqua          #+#    #+#             */
/*   Updated: 2022/07/27 14:06:34 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*get_grid_line(t_map *map, char *str)
{
	char			*res;
	unsigned int	i;

	i = 0;
	res = ft_zalloc(map->width + 1);
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	while (i < map->width)
	{
		res[i] = ' ';
		i++;
	}
	return (res);
}

void	get_grid(t_map *map, int fd)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	map->grid = ft_zalloc(sizeof(char *) * map->height + 1);// получаем строку поля
	while (i < map->height)
	{
		map->grid[i] = get_grid_line(map, \
				ft_strtrim(ft_get_next_line(fd), "\n"));
		j = 0;
		while (map->grid[i][j])
		{
			if (!ft_strchr(" 01SNWE", map->grid[i][j]))
				err_exit("Error!\nWrong symbols in grid");// если неправильный символ в поле
			j++;
		}
		i++;
	}
}

int	check_neighbors(t_map *map, unsigned int i, unsigned int j)
{
	if (i == 0 || j == 0)
		if (ft_strchr("0SNWE", map->grid[i][j]))
			return (1);
	if (i == map->height - 1 || j == map->width - 1)
		if (ft_strchr("0SNWE", map->grid[i][j]))
			return (1);
	if (!ft_strchr("01SNWE", map->grid[i - 1][j]) ||
		!ft_strchr("01SNWE", map->grid[i + 1][j]) ||
		!ft_strchr("01SNWE", map->grid[i][j - 1]) ||
		!ft_strchr("01SNWE", map->grid[i][j + 1]))
		return (1);
	return (0);
}

void	check_grid_borders(t_map *map)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < ft_strlen(map->grid[i]))
		{
			if (ft_strchr("0SNWE", map->grid[i][j]))
			{
				if (check_neighbors(map, i, j))
					err_exit("Error!\nBad borders");// проверка соседних клеток
			}
			j++;
		}
		i++;
	}
}

void	skip_unuseful_lines(t_map *map, int fd)
{
	int	i;

	i = 0;
	while (i++ < map->num_start_grid)// скипаем до поля
		ft_get_next_line(fd);
}
