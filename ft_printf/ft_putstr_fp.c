/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azahid <azahid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 00:51:17 by azahid            #+#    #+#             */
/*   Updated: 2024/11/10 20:53:05 by azahid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr_fp(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s || fd < 0)
	{
		write(fd, "(null)", 6);
		return (6);
	}
	while (*s)
	{
		ft_putchar_fp(*s, fd);
		i++;
		s++;
	}
	return (i);
}
