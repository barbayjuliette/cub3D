/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 12:12:54 by jbarbay           #+#    #+#             */
/*   Updated: 2023/09/06 12:12:57 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*substring;
	size_t		i;
	size_t		j;

	substring = (char *)malloc(sizeof(char) * (len + 1));
	if (!substring)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			substring[j] = s[i];
			j++;
		}
		i++;
	}
	substring[j] = '\0';
	return (substring);
}

// int main(void)
// {
// 	char string[] = "abcdefghijklmnopqrstuvwxyz";
// 	char *substring;
// 	substring = ft_substr(string, 4, 8);
// 	ft_putstr_fd(ft_substr(string, 4, 8), 1);
// 	return 0;
// }
