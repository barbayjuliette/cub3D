/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 11:07:02 by jbarbay           #+#    #+#             */
/*   Updated: 2023/10/10 11:07:11 by jbarbay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

int			ft_process_int(int num);
int			ft_printf(const char *format, ...);
void		ft_put_unsigned_fd(unsigned int n, int fd);
int			ft_putchar_printf(char c, int fd);
void		ft_putnbr_printf(int n, int fd);
int			ft_putstr_printf(char *s, int fd);
int			get_length_num(long num);
int			ft_puthexa(unsigned long int n);
int			ft_puthexa_upcase(unsigned long int n);
int			ft_putptr(unsigned long num);
int			get_length_unsigned(unsigned int num);
int			ft_count_n_hexa(unsigned long int n);
int			ft_process_unsigned_int(int num);
int			ft_process_str(char *str);
int			check_letter_conversion(char format, va_list ptr);

#endif
