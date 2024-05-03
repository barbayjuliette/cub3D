/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolgano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 14:21:56 by akolgano          #+#    #+#             */
/*   Updated: 2023/09/28 14:21:57 by akolgano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <stdint.h>
# ifndef BUFFER_SIZE

#  define BUFFER_SIZE 1000

# endif

char	*ft_strchr_gnl(char *s, int c);
size_t	ft_strlen_gnl(char *s);
char	*ft_strjoin_gnl(char *s1, char *s2);
void	ft_bzero_gnl(void *s, size_t n);
void	*ft_calloc_gnl(size_t elementCount, size_t elementSize);
char	*ft_next(char *buffer);
char	*get_next_line(int fd);
#endif