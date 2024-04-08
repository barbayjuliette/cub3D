/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 11:05:40 by jbarbay           #+#    #+#             */
/*   Updated: 2023/10/10 11:05:45 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_put_unsigned_fd(unsigned int n, int fd)
{
	char	c;

	if (n > 9)
	{
		ft_putnbr_printf(n / 10, fd);
		ft_putnbr_printf(n % 10, fd);
	}
	else
	{
		c = '0' + n;
		ft_putchar_printf(c, fd);
	}
}

int	ft_count_n_hexa(unsigned long int n)
{
	int	length;

	length = 0;
	while (n >= 16)
	{
		n = n / 16;
		length += 1;
	}
	length += 1;
	return (length);
}

int	ft_puthexa(unsigned long int n)
{
	int		count;
	char	*hexa;
	int		i;

	count = ft_count_n_hexa(n);
	i = count - 1;
	hexa = malloc(sizeof(char) * (count + 1));
	hexa[count] = '\0';
	while (i >= 0)
	{
		hexa[i] = "0123456789abcdef"[n % 16];
		n = n / 16;
		i--;
	}
	ft_putstr_printf(hexa, 1);
	free(hexa);
	return (count);
}

int	ft_puthexa_upcase(unsigned long int n)
{
	int		count;
	char	*hexa;
	int		i;

	count = ft_count_n_hexa(n);
	i = count - 1;
	hexa = malloc(sizeof(char) * (count + 1));
	hexa[count] = '\0';
	while (i >= 0)
	{
		hexa[i] = "0123456789ABCDEF"[n % 16];
		n = n / 16;
		i--;
	}
	ft_putstr_printf(hexa, 1);
	free(hexa);
	return (count);
}
