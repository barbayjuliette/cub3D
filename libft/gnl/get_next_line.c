/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <jbarbay@student.42singapore.sg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:46:08 by jbarbay           #+#    #+#             */
/*   Updated: 2024/04/20 19:32:38 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_one_line(char *rem)
{
	int		i;
	char	*line;

	i = 0;
	if (!rem[0])
		return (NULL);
	while (rem[i] && rem[i] != '\n')
		i++;
	if (ft_strchr_gnl(rem, '\n'))
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	ft_strlcpy_gnl(line, rem, i + 1);
	return (line);
}

char	*update_rem(char *rem)
{
	char	*new_rem;
	int		len;
	char	*ret;

	new_rem = ft_strchr_gnl(rem, '\n');
	if (!new_rem)
	{
		free(rem);
		rem = NULL;
		return (NULL);
	}
	new_rem++;
	len = ft_strlen_gnl(new_rem);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	ft_strlcpy_gnl(ret, new_rem, len + 1);
	free(rem);
	rem = NULL;
	return (ret);
}

char	*get_next_line(int fd)
{
	int		bytes_read;
	char	*buffer;
	static char	*rem = NULL;
	char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!rem)
	{
		rem = malloc(1);
		rem[0] = '\0';
	}
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr_gnl(rem, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(rem);
			rem = NULL;
			free(buffer);
			buffer = NULL;
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		rem = ft_strjoin_gnl(rem, buffer);
	}
	free(buffer);
	line = get_one_line(rem);
	rem = update_rem(rem);
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
