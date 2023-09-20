/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:59:55 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/19 12:25:39 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	sh_exit(t_ast_node *node)
{
	int	exit_code;

	if (get_node_arg_count(node) > 1)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: exit: too many arguments\n");
		exit_code = 255;
	}
	if (get_node_arg(node, 0))
	{
		if (ft_isnumber(get_node_arg(node, 0)))
			exit_code = ft_atoi(get_node_arg(node, 0));
		else
		{
			ft_printf_fd(STDERR_FILENO,
				"minishell: exit: %s: numeric argument required\n",
				get_node_arg(node, 0));
			return (255);
		}
	}
	else
		exit_code = 0;
	return (exit_code);
}
