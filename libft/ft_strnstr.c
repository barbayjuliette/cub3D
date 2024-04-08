/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:11:17 by jbarbay           #+#    #+#             */
/*   Updated: 2023/09/06 12:11:20 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*ptr;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	ptr = NULL;
	while (haystack[i] && needle[j] && i < len)
	{
		if (haystack[i] == needle[j])
		{
			j++;
			i++;
		}
		else
		{
			if (j == 0)
				i++;
			else
				j = 0;
		}
	}
	if (!needle[j])
		ptr = (char *)&haystack[i - j];
	return (ptr);
}
