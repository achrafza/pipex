/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_pfu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azahid <azahid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 03:14:54 by azahid            #+#    #+#             */
/*   Updated: 2024/11/10 21:04:31 by azahid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_pfu(unsigned int n, int reset, int fd)
{
	static int	x;

	if (reset)
		x = 0;
	if (n > 9)
		ft_putnbr_pfu(n / 10, 0, fd);
	x++;
	ft_putchar_fp(n % 10 + '0', fd);
	return (x);
}
