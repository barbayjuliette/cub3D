/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:48:05 by jbarbay           #+#    #+#             */
/*   Updated: 2023/09/06 15:48:08 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*string;
	int		i;
	int		j;

	i = 0;
	j = 0;
	string = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!string)
		return (NULL);
	while (s1[i])
	{
		string[j] = s1[i];
		i++;
		j++;
	}
	i = 0;
	while (s2[i])
	{
		string[j] = s2[i];
		i++;
		j++;
	}
	string[j] = '\0';
	return (string);
}

// int	main(int argc, char const *argv[])
// {
// 	ft_putstr_fd(ft_strjoin("hehe  ", "hello"), 1);
// }
