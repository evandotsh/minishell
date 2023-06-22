/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 12:17:06 by evmorvan          #+#    #+#             */
/*   Updated: 2023/04/17 17:34:36 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/**
	* Write the given character to the given file descriptor.
	*
	* @param c The character to write.
	* @param fd The file descriptor to write to.
*/
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
