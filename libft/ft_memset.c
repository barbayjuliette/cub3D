/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:06:43 by jbarbay           #+#    #+#             */
/*   Updated: 2023/09/06 12:06:47 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = (char *)b;
	while (i < len)
	{
		ptr[i] = (char)c;
		i++;
	}
	return (b);
}

// int main(void)
// {
// 	void *b;

// 	int c = 65;
// 	size_t len = 5;
// 	b = malloc(len);
// 	ft_memset(b, c, len);
// 	return 0;
// }