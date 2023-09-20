/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:45:45 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/19 11:43:39 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_random(void)
{
	int	fd;
	int	random_number;

	fd = open("/dev/random", O_RDONLY);
	if (fd == -1)
		return (42);
	read(fd, &random_number, sizeof(int));
	close(fd);
	if (random_number < 0)
		random_number *= -1;
	return (random_number);
}

char	*ft_strndup(char *str, int n)
{
	char	*new_str;

	new_str = malloc(sizeof(char) * (n + 1));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, str, n + 1);
	return (new_str);
}
