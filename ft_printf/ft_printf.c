/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azahid <azahid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 22:02:11 by azahid            #+#    #+#             */
/*   Updated: 2024/11/28 19:38:09 by azahid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_typed1(va_list args, char c)
{
	char	*str;
	int		num;
	int		res;

	num = 0;
	if (c == 'd' || c == 'i')
	{
		res = va_arg(args, int);
		num = ft_putnbr_pf(res, 1, 1);
	}
	else if (c == 'u')
	{
		res = va_arg(args, unsigned int);
		num = ft_putnbr_pfu((unsigned int)res, 1, 1);
	}
	else if (c == 's')
	{
		str = va_arg(args, char *);
		num = ft_putstr_fp(str, 1);
	}
	else if (c == '%')
	{
		ft_putchar_fp(c, num = 1);
	}
	return (num);
}

static int	ft_typed2(va_list args, char c)
{
	int		num;
	size_t	res;
	char	cc;

	num = 0;
	if (c == 'X')
		num = ft_putnbrhexa1(va_arg(args, unsigned int), 1, 1);
	else if (c == 'x')
		num = ft_putnbrhexa2(va_arg(args, unsigned int), 1, 1);
	else if (c == 'c')
	{
		cc = va_arg(args, int);
		num = ft_putchar_fp(cc, 1);
	}
	else if (c == 'p')
	{
		res = va_arg(args, size_t);
		num = ft_putstr_fp("0x", 1);
		num += ft_printadd(res, 1, 1);
	}
	return (num);
}

static int	is_set1(char c)
{
	char	*charset;

	charset = "dius%";
	while (*charset)
	{
		if (*charset == c)
			return (1);
		charset++;
	}
	return (0);
}

static int	is_set2(char c)
{
	char	*charset;

	charset = "cpxX";
	while (*charset)
	{
		if (*charset == c)
			return (1);
		charset++;
	}
	return (0);
}

int	ft_printf(const char *str, ...)
{
	int		count;
	va_list	args;

	if (write(1, 0, 0) == -1)
		return (-1);
	va_start(args, str);
	count = 0;
	while (*str)
	{
		while (*str && *str != '%')
		{
			ft_putchar_fp(*str, 1);
			str++;
			count++;
		}
		if (*str == '%' && is_set1(*(str + 1)))
			count += ft_typed1(args, *(++str));
		else if (*str == '%' && is_set2(*(str + 1)))
			count += ft_typed2(args,*(++str));
		if (*str)
			str++;
	}
	va_end(args);
	return (count);
}
