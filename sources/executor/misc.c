/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 21:57:34 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/25 09:22:11 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_builtins(t_ast_node *node, t_env *env, char **args)
{
	int	ret;

	ret = -1337;
	if (ft_strcmp(node->cmd_name, "echo") == 0)
		ret = sh_echo(node, env);
	else if (ft_strcmp(node->cmd_name, "env") == 0)
		ret = sh_env(env);
	else if (ft_strcmp(node->cmd_name, "pwd") == 0)
		ret = sh_pwd(env);
	if (ret != -1337)
	{
		free_split(args);
		exit(ret);
	}
}
