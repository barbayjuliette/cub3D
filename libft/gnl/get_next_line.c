/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:46:08 by jbarbay           #+#    #+#             */
/*   Updated: 2024/04/08 22:09:07 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	has_new_line(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*get_one_line(char *rem, int size)
{
	char	*line;
	int		i;

	if (size == 0)
	{
		line = ft_strdup_gnl(rem);
		return (line);
	}
	line = (char *)malloc(sizeof(char) * (size + 1));
	if (!line)
		return (NULL);
	line[size] = '\0';
	i = 0;
	while (i < size)
	{
		line[i] = rem[i];
		i++;
	}
	return (line);
}

int	read_file(char **rem, char **buffer, int fd)
{
	int	bytes_read;

	bytes_read = read(fd, *buffer, BUFFER_SIZE);
	if (bytes_read < 1)
		return (bytes_read);
	(*buffer)[bytes_read] = '\0';
	ft_strjoin_gnl(rem, *buffer);
	return (bytes_read);
}

char	*free_static(char **rem, char **buff)
{
	char	*temp;

	temp = *rem;
	*rem = NULL;
	free(temp);
	temp = NULL;
	free(*buff);
	*buff = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	int			bytes_read;
	char		*line;
	static char	*rem;
	int			index_line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!rem)
		rem = ft_calloc_gnl(1);
	bytes_read = 1;
	while (bytes_read > 0 && has_new_line(rem) == -1)
	{
		bytes_read = read_file(&rem, &buffer, fd);
		if (bytes_read < 0)
			return (free_static(&rem, &buffer));
	}
	free(buffer);
	index_line = has_new_line(rem);
	line = get_one_line(rem, index_line + 1);
	ft_substr_gnl(&rem, index_line + 1, ft_slen(rem) - index_line, 0);
	if (ft_slen(rem) == 0 && ft_slen(line) == 0)
		return (free_static(&rem, &line));
	return (line);
}

// int	main(void)
// {
// 	// int	fd;
// 	// fd = open("test.txt", O_RDONLY);
// 	char *line;

// 	line = get_next_line(9);
// 	while (line)
// 	{
// 		printf("Line: %s", line);
// 		free(line);
// 		line = get_next_line(9);
// 	}
// 	free(line);
// 	close(9);

// 	return (0);
// }
