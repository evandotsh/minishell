/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 06:57:23 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/22 08:03:21 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	sh_echo(t_ast_node *node)
{
	int		is_n;
	int		i;
	int		j;
	char	*arg;

	is_n = 0;
	i = 0;
	arg = get_node_arg(node, 0);
	if (arg && arg[0] == '-')
	{
		j = 1;
		while (arg[j] == 'n')
			j++;
		if (arg[j] == '\0')
			is_n = 1;
	}
	while (get_node_arg(node, i + is_n))
	{
		printf("%s", get_node_arg(node, i + is_n));
		if (get_node_arg(node, i + is_n + 1))
			printf(" ");
		i++;
	}
	if (!is_n)
		printf("\n");
	return (0);
}
