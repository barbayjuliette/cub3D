/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:46:24 by jbarbay           #+#    #+#             */
/*   Updated: 2024/04/08 22:09:17 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_slen(char *string)
{
	int	i;

	i = 0;
	while (string[i] != '\0')
		i++;
	return (i);
}

void	ft_strjoin_gnl(char **s1, char *s2)
{
	char	*string;
	int		i;
	int		j;

	i = 0;
	j = 0;
	string = (char *)malloc((ft_slen(*s1) + ft_slen(s2) + 1) * sizeof(char));
	if (!string || !*s1 || !s2)
		return ;
	while ((*s1)[i])
	{
		string[j] = (*s1)[i];
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
	free(*s1);
	*s1 = string;
}

void	ft_substr_gnl(char **s, unsigned int start, size_t len, size_t i)
{
	char		*substring;
	size_t		j;

	if (has_new_line(*s) == -1)
	{
		free(*s);
		*s = ft_strdup_gnl("");
		return ;
	}
	substring = (char *)malloc(sizeof(char) * (len + 1));
	if (!substring)
		return ;
	j = 0;
	while ((*s)[i])
	{
		if (i >= start && j < len)
		{
			substring[j] = (*s)[i];
			j++;
		}
		i++;
	}
	substring[j] = '\0';
	free(*s);
	*s = substring;
}

char	*ft_strdup_gnl(char *s1)
{
	int		len;
	int		i;
	char	*copy;

	len = ft_slen(s1);
	i = 0;
	copy = (char *)malloc(sizeof(char) * (len + 1));
	if (!copy)
		return (NULL);
	while (s1[i])
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

void	*ft_calloc_gnl(size_t size)
{
	char	*ptr;
	size_t	i;

	i = 0;
	ptr = malloc(size);
	if (ptr == NULL)
		return (NULL);
	while (i < size)
	{
		ptr[i] = '\0';
		i++;
	}
	return (ptr);
}
