/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 19:21:51 by jbarbay           #+#    #+#             */
/*   Updated: 2023/10/13 19:21:56 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_process_int(int num)
{
	ft_putnbr_printf(num, 1);
	return (get_length_num(num));
}

int	ft_process_unsigned_int(int num)
{
	ft_put_unsigned_fd(num, 1);
	return (get_length_unsigned(num));
}

int	ft_process_str(char *str)
{
	if (str == NULL)
	{
		ft_putstr_printf("(null)", 1);
		return (6);
	}
	else
	{
		return (ft_putstr_printf(str, 1));
	}
}

int	ft_putptr(unsigned long num)
{
	if (num == 0)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	ft_putchar_printf('0', 1);
	ft_putchar_printf('x', 1);
	return (ft_puthexa(num)+ 2);
}
