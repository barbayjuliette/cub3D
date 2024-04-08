/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 14:31:41 by jbarbay           #+#    #+#             */
/*   Updated: 2023/09/07 14:31:44 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// 
// static void	f(unsigned int i, char *c)
// {
// 	*c = (char)ft_toupper((int)*c);
// }

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

// int	main(void)
// {	
// 	char	string[] = "hello";

// 	ft_striteri(string, f);
// 	printf("%s\n", string);
// 	return 0;
// }