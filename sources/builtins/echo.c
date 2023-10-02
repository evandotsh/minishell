/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 06:57:23 by evmorvan          #+#    #+#             */
/*   Updated: 2023/10/01 23:58:30 by evmorvan         ###   ########.fr       */
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
	int		j;
	char	*arg;

	is_n = 0;
	i = 0;
	while (get_node_arg(node, i) && get_node_arg(node, i)[0] == '-')
	{
		arg = get_node_arg(node, i);
		j = 1;
		while (arg[j] == 'n')
			j++;
		if (arg[j] == '\0')
			is_n++;
		i++;
	}
	echo(node, is_n);
	if (!is_n)
		printf("\n");
	env_set(env, "?", "0");
	return (0);
}
