/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:07:26 by jbarbay           #+#    #+#             */
/*   Updated: 2023/09/06 12:07:32 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*source;
	char	*destination;
	size_t	i;

	if (dest == NULL)
		return (NULL);
	source = (char *)src;
	destination = (char *)dest;
	i = 0;
	while (i < n)
	{
		destination[i] = source[i];
		i++;
	}
	return (dest);
}
