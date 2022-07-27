/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwitch <rtwitch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:37:17 by majacqua          #+#    #+#             */
/*   Updated: 2022/07/27 14:20:50 by rtwitch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map	*get_map(char *filename)
{
	t_map	*map;
	int		fd;

	map = init_map();// инициализации карты
	fd = open(filename, O_RDONLY);
	get_properties(map, fd);// получение данных
	close(fd);
	fd = open(filename, O_RDONLY);
	skip_unuseful_lines(map, fd);
	get_grid(map, fd);// получение поля
	close(fd);
	check_grid_borders(map);// проверка границ поля
	check_assets_path(map);// проверка путей ассетов
	return (map);
}

int	main(int argc, char **argv)
{
	t_env	env;

	validate_input(argc, argv);// валидация аргументов
	env.map = get_map(argv[1]);// создание карты
	env.size = (float)RES_X / (float)env.map->width;// шаг, между разрешением окна и шириной карты
	env.player = create_player(env.map, &env);// создание игрока
	env.mlx = mlx_init();// инициализация mlx
	env.map->no_img = new_img_xpm(env.mlx, env.map->no_path);// наши картинки 
	env.map->so_img = new_img_xpm(env.mlx, env.map->so_path);
	env.map->ea_img = new_img_xpm(env.mlx, env.map->ea_path);
	env.map->we_img = new_img_xpm(env.mlx, env.map->we_path);
	env.win = mlx_new_window(env.mlx, RES_X, RES_Y, "Game");// создание окна
	render(&env);// рендер
	set_hooks(&env);// нажатие клавиш
	mlx_loop(env.mlx);// залупливание
	return (0);
}
