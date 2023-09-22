/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 21:57:34 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/22 08:09:35 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_builtins(t_ast_node *node, t_env *env, char **args)
{
	int	ret;

	ret = -1337;
	if (ft_strncmp(node->cmd_name, "echo", 5) == 0)
		ret = sh_echo(node);
	else if (ft_strncmp(node->cmd_name, "env", 4) == 0)
		ret = sh_env(env);
	else if (ft_strncmp(node->cmd_name, "pwd", 4) == 0)
		ret = sh_pwd();
	else if (ft_strncmp(node->cmd_name, "cd", 3) == 0)
		ret = sh_cd(node, env);
	if (ret != -1337)
	{
		free_split(args);
		exit(ret);
	}
}
