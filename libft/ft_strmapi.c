/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 13:48:06 by jbarbay           #+#    #+#             */
/*   Updated: 2023/09/07 13:48:12 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static char	f(unsigned int i, char c)
// {
// 	c = ft_toupper(c);
// 	return (c);
// }

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*string;
	int		length;
	int		i;

	i = 0;
	length = ft_strlen(s);
	string = (char *)malloc((length + 1) * sizeof(char));
	if (!string)
		return (NULL);
	while (s[i])
	{
		string[i] = f(i, s[i]);
		i++;
	}
	string[i] = '\0';
	return (string);
}

// int	main(void)
// {	
// 	char	*string;

// 	string = ft_strmapi("hello", f);
// 	printf("%s\n", string);
// 	return 0;
// }