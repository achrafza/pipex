/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrhexa2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azahid <azahid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 01:17:27 by azahid            #+#    #+#             */
/*   Updated: 2024/11/10 21:06:00 by azahid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbrhexa2(int n, int reset, int fd)
{
	unsigned int	num;
	static int		x;
	char			*hexa;

	hexa = "0123456789abcdef";
	num = (unsigned int)n;
	if (reset)
		x = 0;
	if (num > 15)
		ft_putnbrhexa2(num / 16, 0, fd);
	x++;
	ft_putchar_fp(hexa[num % 16], fd);
	return (x);
}
