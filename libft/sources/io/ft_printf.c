/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 18:29:42 by evmorvan          #+#    #+#             */
/*   Updated: 2023/04/09 15:23:14 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_formatter(va_list args, char fmt)
{
	int	len;

	len = 0;
	if (fmt == 'c')
		len += ft_putchar((char) va_arg(args, int));
	if (fmt == 's')
		len += ft_putstr(va_arg(args, char *));
	if (fmt == 'p')
		len += ft_putptr(va_arg(args, unsigned long long));
	if (fmt == 'd' || fmt == 'i')
		len += ft_putnbr(va_arg(args, int));
	if (fmt == 'u')
		len += ft_putuint(va_arg(args, unsigned int));
	if (fmt == 'x')
		len += ft_puthex(va_arg(args, unsigned int), 1);
	if (fmt == 'X')
		len += ft_puthex(va_arg(args, unsigned int), 0);
	if (fmt == '%')
		len += ft_putchar('%');
	return (len);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	args;
	int		i;
	int		len;

	i = 0;
	len = 0;
	va_start(args, fmt);
	while (fmt[i] != '\0')
	{
		if (fmt[i] == '%')
			len += ft_formatter(args, fmt[++i]);
		else
			len += ft_putchar(fmt[i]);
		i++;
	}
	va_end(args);
	return (len);
}
