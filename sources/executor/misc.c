/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 21:57:34 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/28 15:11:30 by evmorvan         ###   ########.fr       */
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
	else if (ft_strcmp(node->cmd_name, "unset") == 0)
		ret = sh_unset(node, env);
	else if (ft_strcmp(node->cmd_name, "export") == 0)
		ret = sh_export(node, env);
	else if (ft_strcmp(node->cmd_name, "exit") == 0)
		ret = sh_exit(node, env);
	else if (ft_strcmp(node->cmd_name, "cd") == 0)
		ret = sh_cd(node, env);
	if (ret != -1337)
	{
		if (args)
		{
			free_split(args);
			exit(ret);
		}
	}
}

int	is_builtin(char *cmd_name)
{
	if (ft_strcmp(cmd_name, "echo") == 0 || ft_strcmp(cmd_name, "env") == 0
		|| ft_strcmp(cmd_name, "pwd") == 0 || ft_strcmp(cmd_name, "unset") == 0
		|| ft_strcmp(cmd_name, "export") == 0 || ft_strcmp(cmd_name, "exit")
		== 0 || ft_strcmp(cmd_name, "cd") == 0)
		return (1);
	return (0);
}

void	empty_handler(int sig)
{
	if (sig == SIGINT)
		ft_printf("^C\n");
	else if (sig == SIGQUIT)
		ft_printf("^\\Quit: 3\n");
}
