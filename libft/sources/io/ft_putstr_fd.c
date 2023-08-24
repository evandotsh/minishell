/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 12:18:26 by evmorvan          #+#    #+#             */
/*   Updated: 2023/04/17 17:34:43 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/**
	* Write the given string to the given file descriptor.
	*
	* @param s The string to write.
	* @param fd The file descriptor to write to.
*/
void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	if (!s)
		return ;
	while (i != ft_strlen(s))
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}
