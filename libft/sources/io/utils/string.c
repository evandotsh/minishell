/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 11:52:40 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/11 14:35:19 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

int	pf_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	if (!s)
	{
		pf_putstr_fd("(null)", fd);
		return (6);
	}
	while (s[i] != '\0')
	{
		pf_putchar_fd(s[i], fd);
		i++;
	}
	return ((int) i);
}

int	pf_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}
