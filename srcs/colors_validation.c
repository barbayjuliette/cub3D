/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:40:40 by jbarbay           #+#    #+#             */
/*   Updated: 2024/04/09 13:44:01 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	parsing_error_colors(char *str)
{
	ft_putendl_fd("Error", 1);
	ft_putendl_fd(str, 1);
	return (1);
}

int	check_color_format(char c, int i, int num)
{
	if (i < 2 && c != ',')
		return (parsing_error_colors("Wrong format for color"));
	else if (i == 2 && c != '\n')
		return (parsing_error_colors("Too many args after colors"));
	else if (num < 0 || num > 255)
		return (parsing_error_colors("R,G,B colors must be in range [0,255]"));
	return (0);
}

int	get_colors(int *colors, char *arg)
{
	int	num;
	int	i;
	int	index;

	i = 0;
	index = 0;
	while (i < 3)
	{
		num = 0;
		while (ft_isdigit(arg[index]))
		{
			num = num * 10 + arg[index] - '0';
			index++;
		}
		if (check_color_format(arg[index], i, num))
			return (1);
		colors[i] = num;
			index++;
		i++;
	}
	return (0);
}
