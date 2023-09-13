/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 11:57:32 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/11 14:30:27 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

int	pf_ptrlen(uintptr_t ptr)
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

void	pf_ptr(uintptr_t num, int fd)
{
	if (num >= 16)
	{
		pf_ptr(num / 16, fd);
		pf_ptr(num % 16, fd);
	}
	else
	{
		if (num <= 9)
			pf_putchar_fd((num + '0'), fd);
		else
			pf_putchar_fd((num - 10 + 'a'), fd);
	}
}

int	pf_putptr_fd(unsigned long long ptr, int fd)
{
	int	print_length;

	print_length = 0;
	print_length += write(fd, "0x", 2);
	if (ptr == 0)
		print_length += write(fd, "0", 1);
	else
	{
		pf_ptr(ptr, fd);
		print_length += pf_ptrlen(ptr);
	}
	return (print_length);
}
