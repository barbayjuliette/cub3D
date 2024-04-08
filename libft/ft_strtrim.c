/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:17:20 by jbarbay           #+#    #+#             */
/*   Updated: 2023/09/06 16:17:26 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	to_trim(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static	int	find_pos_start(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (s1[i] && to_trim(s1[i], set))
		i++;
	return (i);
}

static int	find_pos_end(char const *s1, char const *set, int start)
{
	int	i;

	i = ft_strlen(s1) - 1;
	while (s1[i] && to_trim(s1[i], set) && i > start)
		i--;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	char	*string;
	int		pos_end;
	int		pos_start;

	if (!s1 || !set)
		return (NULL);
	pos_start = find_pos_start(s1, set);
	pos_end = find_pos_end(s1, set, pos_start);
	len = pos_end - pos_start + 1;
	string = ft_substr(s1, pos_start, len);
	return (string);
}

// int main(void)
// {
// 	printf("String: %s\n", ft_strtrim("aaaaaa", "a"));
// 	return(0);
// }
