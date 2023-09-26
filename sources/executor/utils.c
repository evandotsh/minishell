/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 21:09:27 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/26 16:42:49 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**build_argv(t_ast_node *node)
{
	char	**args;
	int		i;

	i = 0;
	args = malloc((node->cmd_arg_count + 2) * sizeof(char *));
	args[0] = node->cmd_name;
	while (i < node->cmd_arg_count)
	{
		args[i + 1] = node->cmd_args[i]->arg_value;
		i++;
	}
	args[node->cmd_arg_count + 1] = NULL;
	return (args);
}

void	setup_redirections(t_ast_node *node)
{
	int	in;
	int	out;

	if (node->cmd_stdin_file)
	{
		in = open(node->cmd_stdin_file, O_RDONLY);
		if (in == -1)
			error(node->cmd_name, strerror(errno));
		dup2(in, STDIN_FILENO);
		close(in);
	}
	if (node->cmd_stdout_file)
	{
		if (node->cmd_stdout_dest == 1)
			out = open(node->cmd_stdout_file, O_WRONLY | O_TRUNC | O_CREAT,
					0644);
		else
			out = open(node->cmd_stdout_file, O_APPEND | O_WRONLY,
					0644);
		if (out == -1)
			error(node->cmd_name, strerror(errno));
		dup2(out, STDOUT_FILENO);
		close(out);
	}
}

void	error(char *cmd_name, char *error)
{
	ft_printf_fd(STDERR_FILENO, "minishell: %s: %s\n", cmd_name, error);
}

void	pidis0(t_ast_node *node, t_env *env, int *pipefd, int fd)
{
	if (fd == STDOUT_FILENO)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		executor(node->pipe_lhs, env);
		exit(0);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		executor(node->pipe_rhs, env);
		exit(0);
	}
}

void	closepipes(int *pipefd)
{
	close(pipefd[0]);
	close(pipefd[1]);
}
