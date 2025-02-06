/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printad.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azahid <azahid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 23:06:07 by azahid            #+#    #+#             */
/*   Updated: 2024/11/10 21:05:15 by azahid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printadd(size_t n, int reset, int fd)
{
	static int	x;
	char		*hexa;

	if (reset)
		x = 0;
	hexa = "0123456789abcdef";
	if (n > 15)
		ft_printadd(n / 16, 0, fd);
	x++;
	ft_putchar_fp(hexa[n % 16], fd);
	return (x);
}
