/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:40:31 by jbarbay           #+#    #+#             */
/*   Updated: 2023/09/06 17:40:36 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	count_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			count++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (count);
}

static int	get_length_word(char const *str, char c)
{
	int	length;

	length = 0;
	while (str[length] != c && str[length])
		length++;
	return (length);
}

static char	*get_word(char const *str, char c)
{
	int		i;
	char	*word;
	int		length;

	length = get_length_word(str, c);
	word = (char *)malloc((length + 1) * sizeof(char));
	i = 0;
	if (!word)
		return (NULL);
	while (i < length)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	int		total_words;
	char	**strings;
	int		j;

	total_words = count_words(s, c);
	strings = (char **)malloc((total_words + 1) * sizeof(char *));
	if (!strings)
		return (NULL);
	j = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			strings[j] = get_word(s, c);
			s = s + get_length_word(s, c);
			j++;
		}
	}
	strings[j] = NULL;
	return (strings);
}

// int main(void)
// {
// 	int	i;
// 	char **strings;

// 	i = 0;
// strings = ft_split("hello how are you", ' ');
	// while (strings[i])
// 	{
// 		ft_putstr_fd(strings[i], 1);
// 		free(strings[i]);
// 		write(1, "\n", 1);
// 		i++;
// 	}
// 	free(strings);
// 	return (0);
// }
