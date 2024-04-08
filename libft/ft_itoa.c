/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:13:09 by jbarbay           #+#    #+#             */
/*   Updated: 2023/09/06 12:13:13 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_length_num(long num)
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

char	*ft_itoa(int n)
{
	int		len;
	char	*string;
	int		digit;
	long	num;

	num = n;
	len = get_length_num(num) - 1;
	string = (char *)malloc(sizeof(char) * (len + 2));
	if (!string)
		return (NULL);
	string[len + 1] = '\0';
	if (num < 0)
	{
		num = -num;
		string[0] = '-';
	}
	while (num > 9)
	{
		digit = num % 10;
		num = num / 10;
		string[len] = '0' + digit;
		len--;
	}
	string[len] = '0' + num;
	return (string);
}
