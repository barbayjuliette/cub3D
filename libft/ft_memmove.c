/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:08:23 by jbarbay           #+#    #+#             */
/*   Updated: 2023/09/06 12:08:26 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char	*source;
	char	*destination;

	source = (char *)src;
	destination = (char *)dest;
	if (dest < src)
		return (ft_memcpy(dest, src, len));
	else
	{
		while (len > 0)
		{
			len--;
			destination[len] = source[len];
		}
	}
	return (dest);
}
