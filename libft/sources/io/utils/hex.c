/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 12:05:15 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/11 15:40:08 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

int	ft_hexlen(unsigned	int num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		len++;
		num = num / 16;
	}
	return (len);
}

void	ft_hex(unsigned int num, int is_lower)
{
	if (num >= 16)
	{
		ft_hex(num / 16, is_lower);
		ft_hex(num % 16, is_lower);
	}
	else
	{
		if (num <= 9)
			ft_putchar_fd((num + '0'), 1);
		else
		{
			if (is_lower)
				ft_putchar_fd((num - 10 + 'a'), 1);
			else
				ft_putchar_fd((num - 10 + 'A'), 1);
		}
	}
}

int	pf_puthex_fd(unsigned int num, int is_lower, int fd)
{
	if (num == 0)
		return (write(fd, "0", 1));
	else
		ft_hex(num, is_lower);
	return (ft_hexlen(num));
}
