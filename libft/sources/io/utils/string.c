/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 11:52:40 by evmorvan          #+#    #+#             */
/*   Updated: 2023/04/09 15:23:13 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

int	ft_putstr(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
	{
		ft_putstr("(null)");
		return (6);
	}
	while (s[i] != '\0')
	{
		ft_putchar(s[i]);
		i++;
	}
	return ((int) i);
}

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}
