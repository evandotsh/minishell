/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 06:43:32 by evmorvan          #+#    #+#             */
/*   Updated: 2023/10/02 00:32:49 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	executor(t_ast_node *node, t_env *env)
{
	if (node == NULL)
		return ;
	if (node->type == ND_CMD)
	{
		if (is_builtin(node->cmd_name) && node->cmd_stdin_file == NULL
			&& node->cmd_stdout_file == NULL)
			execute_builtins(node, env, NULL);
		else
			execute_command(node, env);
	}
	else if (node->type == ND_PIPE)
		execute_pipe(node, env);
}

void	execute_command(t_ast_node *node, t_env *env)
{
	int		status;
	pid_t	pid;
	char	*tmp;

	pid = fork();
	if (pid == 0)
	{
		setup_redirections(node);
		launch_process(node, env);
	}
	else
	{
		node->cmd_pid = pid;
		signal(SIGINT, empty_handler);
		signal(SIGQUIT, empty_handler);
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
			tmp = ft_itoa((128 + WTERMSIG(status)));
		else
			tmp = ft_itoa(WEXITSTATUS(status));
		if (ft_strcmp(tmp, "139") == 0)
			ft_printf("Segmentation fault\n");
		env_set(env, "?", tmp);
		free(tmp);
	}
}

void	execute_pipe(t_ast_node *node, t_env *env)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(pipefd) < 0)
		return (error(node->cmd_name, "pipe failed"));
	pid1 = fork();
	if (pid1 < 0)
		return (error(node->cmd_name, "fork failed"));
	if (pid1 == 0)
		pidis0(node, env, pipefd, STDOUT_FILENO);
	else
	{
		pid2 = fork();
		if (pid2 < 0)
			return (error(node->cmd_name, "fork failed"));
		if (pid2 == 0)
			pidis0(node, env, pipefd, STDIN_FILENO);
		else
		{
			closepipes(pipefd);
			wait(NULL);
			wait(NULL);
		}
	}
}

void	_error(t_env *env)
{
	ft_printf_fd(STDERR_FILENO, "minishell: execve error\n");
	env_set(env, "?", "1");
}

void	launch_process(t_ast_node *node, t_env *env)
{
	char	**args;
	int		ret;
	char	*path;
	char	**formatted_env;

	args = build_argv(node);
	execute_builtins(node, env, args);
	path = get_exec_path_from_env(args[0], env);
	if (!path || is_executable(path) == 1)
		handle_command_not_found(args, path);
	if (is_directory(path) == 1)
		handle_path_is_directory(args, path);
	formatted_env = env_to_envp_format(env);
	ret = execve(path, args, formatted_env);
	free_split(formatted_env);
	free(path);
	free_split(args);
	if (ret == -1)
		_error(env);
	exit(1);
}
