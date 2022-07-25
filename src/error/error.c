/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majacqua <majacqua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 16:17:35 by majacqua          #+#    #+#             */
/*   Updated: 2022/07/25 13:23:14 by majacqua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

int	err_exit(char *text)
{
	ft_putstr_fd("Error! Cub3D: ", 2);
	ft_putstr_fd(text, 2);
	ft_putstr_fd("\n", 2);
	ft_free();
	exit(1);
}