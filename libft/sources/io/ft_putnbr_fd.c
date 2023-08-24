/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 12:21:39 by evmorvan          #+#    #+#             */
/*   Updated: 2023/04/17 17:34:41 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/**
	* Write the given integer to the given file descriptor.
	*
	* @param n The integer to write.
	* @param fd The file descriptor to write to.
*/
void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	if (n >= 10)
		ft_putnbr_fd(n / 10, fd);
	c = ((n % 10) + '0');
	write(fd, &c, 1);
}
