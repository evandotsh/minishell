/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 18:29:42 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/11 15:38:47 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	pf_formatter_fd(int fd, va_list args, char fmt)
{
	int	len;

	len = 0;
	if (fmt == 'c')
		len += pf_putchar_fd((char) va_arg(args, int), fd);
	if (fmt == 's')
		len += pf_putstr_fd(va_arg(args, char *), fd);
	if (fmt == 'p')
		len += pf_putptr_fd(va_arg(args, unsigned long long), fd);
	if (fmt == 'd' || fmt == 'i')
		len += pf_putnbr_fd(va_arg(args, int), fd);
	if (fmt == 'u')
		len += pf_putuint_fd(va_arg(args, unsigned int), fd);
	if (fmt == 'x')
		len += pf_puthex_fd(va_arg(args, unsigned int), 1, fd);
	if (fmt == 'X')
		len += pf_puthex_fd(va_arg(args, unsigned int), 0, fd);
	if (fmt == '%')
		len += pf_putchar_fd('%', fd);
	return (len);
}

int	ft_printf_fd(int fd, const char *fmt, ...)
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
			len += pf_formatter_fd(fd, args, fmt[++i]);
		else
			len += pf_putchar_fd(fmt[i], fd);
		i++;
	}
	va_end(args);
	return (len);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	args;
	int		i;
	int		len;
	int		fd;

	i = 0;
	len = 0;
	fd = 0;
	va_start(args, fmt);
	while (fmt[i] != '\0')
	{
		if (fmt[i] == '%')
			len += pf_formatter_fd(fd, args, fmt[++i]);
		else
			len += pf_putchar_fd(fmt[i], fd);
		i++;
	}
	va_end(args);
	return (len);
}
