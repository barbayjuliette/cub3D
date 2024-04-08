/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   library.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:49:25 by jbarbay           #+#    #+#             */
/*   Updated: 2023/10/10 16:49:30 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_printf(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

int	get_length_num(long num)
{
	int	length;

	length = 1;
	if (num < 0)
	{
		length++;
		num = -num;
	}
	while (num > 9)
	{
		num = num / 10;
		length++;
	}
	return (length);
}

int	get_length_unsigned(unsigned int num)
{
	int	length;

	length = 1;
	while (num > 9)
	{
		num = num / 10;
		length++;
	}
	return (length);
}

void	ft_putnbr_printf(int n, int fd)
{
	long	num;
	char	c;

	num = n;
	if (num < 0)
	{
		num = -num;
		ft_putchar_printf('-', fd);
	}
	if (num > 9)
	{
		ft_putnbr_printf(num / 10, fd);
		ft_putnbr_printf(num % 10, fd);
	}
	else
	{
		c = '0' + num;
		ft_putchar_printf(c, fd);
	}
}

int	ft_putstr_printf(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		ft_putchar_printf(s[i], fd);
		i++;
	}
	return (i);
}
