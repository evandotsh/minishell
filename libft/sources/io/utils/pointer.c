/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 11:57:32 by evmorvan          #+#    #+#             */
/*   Updated: 2023/04/09 15:23:12 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

int	ft_ptrlen(uintptr_t ptr)
{
	int	len;

	len = 0;
	while (ptr != 0)
	{
		len++;
		ptr = ptr / 16;
	}
	return (len);
}

void	ft_ptr(uintptr_t num)
{
	if (num >= 16)
	{
		ft_ptr(num / 16);
		ft_ptr(num % 16);
	}
	else
	{
		if (num <= 9)
			ft_putchar_fd((num + '0'), 1);
		else
			ft_putchar_fd((num - 10 + 'a'), 1);
	}
}

int	ft_putptr(unsigned long long ptr)
{
	int	print_length;

	print_length = 0;
	print_length += write(1, "0x", 2);
	if (ptr == 0)
		print_length += write(1, "0", 1);
	else
	{
		ft_ptr(ptr);
		print_length += ft_ptrlen(ptr);
	}
	return (print_length);
}
