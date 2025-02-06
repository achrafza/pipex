/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_pf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azahid <azahid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 00:46:52 by azahid            #+#    #+#             */
/*   Updated: 2024/11/10 21:04:14 by azahid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_pf(int n, int reset, int fd)
{
	long		num;
	static int	x;

	num = (long)n;
	if (reset)
		x = 0;
	if (n < 0)
	{
		num = -num;
		write(fd, "-", 1);
		x++;
	}
	if (num > 9)
		ft_putnbr_pf(num / 10, 0, fd);
	x += ft_putchar_fp(num % 10 + '0', fd);
	return (x);
}
