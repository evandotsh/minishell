/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 06:57:23 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/11 12:20:25 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	sh_echo(t_ast_node *node)
{
	int	is_n;
	int	i;

	is_n = 0;
	i = 0;
	if (ft_strncmp(get_node_arg(node, 0), "-n", 3) == 0)
		is_n = 1;
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
