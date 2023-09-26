/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 06:57:23 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/25 20:58:53 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	echo(t_ast_node *node, int is_n)
{
	int	i;

	i = 0;
	while (get_node_arg(node, i + is_n))
	{
		printf("%s", get_node_arg(node, i + is_n));
		if (get_node_arg(node, i + is_n + 1))
			printf(" ");
		i++;
	}
}

int	sh_echo(t_ast_node *node, t_env *env)
{
	int		is_n;
	int		i;
	char	*arg;

	is_n = 0;
	arg = get_node_arg(node, 0);
	if (arg && arg[0] == '-')
	{
		i = 1;
		while (arg[i] == 'n')
			i++;
		if (arg[i] == '\0')
			is_n = 1;
	}
	echo(node, is_n);
	if (!is_n)
		printf("\n");
	env_set(env, "?", "0");
	return (0);
}
