/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azahid <azahid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 21:47:57 by azahid            #+#    #+#             */
/*   Updated: 2024/11/10 21:03:30 by azahid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int	ft_putchar_fp(char c, int fd);
int	ft_putnbr_pf(int n, int reset, int fd);
int	ft_putnbrhexa1(int n, int reset, int fd);
int	ft_putnbrhexa2(int n, int reset, int fd);
int	ft_putstr_fp(char *s, int fd);
int	ft_putnbr_pfu(unsigned int n, int reset, int fd);
int	ft_printadd(size_t n, int reset, int fd);
int	ft_printf(const char *str, ...);

#endif
