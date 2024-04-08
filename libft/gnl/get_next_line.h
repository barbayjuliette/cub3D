/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:46:46 by jbarbay           #+#    #+#             */
/*   Updated: 2023/10/18 18:20:08 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <unistd.h>
# include <stdlib.h>

int		ft_slen(char *string);
void	ft_strjoin(char **s1, char *s2);
void	ft_substr(char **s, unsigned int start, size_t len, size_t i);
int		has_new_line(char *buffer);
char	*get_one_line(char *rem, int size);
char	*get_next_line(int fd);
char	*ft_strdup(char *s1);
void	*ft_calloc(size_t size);
char	*ft_free(char **buffer);
int		read_file(char **rem, char **buffer, int fd);
char	*free_static(char **rem, char **buff);

#endif
