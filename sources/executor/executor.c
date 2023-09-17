/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 06:43:32 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/14 12:19:54 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	test_signal(int sig)
{
	(void) sig;
	printf("FUN HELLO\n");
}

void	executor(t_ast_node *node, t_env *env)
{
	if (node == NULL)
		return ;
	if (node->type == ND_CMD)
		execute_command(node, env);
	else if (node->type == ND_PIPE)
		execute_pipe(node, env);
}

void	execute_command(t_ast_node *node, t_env *env)
{
	int		status;
	pid_t	pid;
	int		ret;

	if (strncmp(node->cmd_name, "unset", 5) == 0)
	{
		sh_unset(node, env);
		return ;
	}
	if (strncmp(node->cmd_name, "export", 6) == 0)
	{
		sh_export(node, env);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		setup_redirections(node);
		launch_process(node, env);
	}
	else
	{
		node->cmd_pid = pid;
		waitpid(pid, &status, 0);
		ret = WEXITSTATUS(status);
		if (ret == 127)
			node->cmd_termination_code = 127;
		else if (ret == 1)
			node->cmd_termination_code = 1;
		else
			node->cmd_termination_code = 0;
		printf("Termination code: %d\n", node->cmd_termination_code);
	}
}

void	execute_pipe(t_ast_node *node, t_env *env)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(pipefd) < 0)
	{
		fprintf(stderr, "Pipe failed.\n");
		return ;
	}
	pid1 = fork();
	if (pid1 < 0)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: %s: %s\n", node->cmd_name,
			"fork failed");
		return ;
	}
	if (pid1 == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		executor(node->pipe_lhs, env);
		exit(0);
	}
	else
	{
		pid2 = fork();
		if (pid2 < 0)
		{
			ft_printf_fd(STDERR_FILENO, "minishell: %s: %s\n", node->cmd_name,
				"fork failed");
			return ;
		}
		if (pid2 == 0)
		{
			close(pipefd[1]);
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
			executor(node->pipe_rhs, env);
			exit(0);
		}
		else
		{
			close(pipefd[0]);
			close(pipefd[1]);
			wait(NULL);
			wait(NULL);
		}
	}
}

void	setup_redirections(t_ast_node *node)
{
	int	in;
	int	out;

	if (node->cmd_stdin_file)
	{
		in = open(node->cmd_stdin_file, O_RDONLY);
		dup2(in, STDIN_FILENO);
		close(in);
	}
	if (node->cmd_stdout_file)
	{
		if (node->cmd_stdout_dest == 1)
			out = open(node->cmd_stdout_file, O_WRONLY | O_TRUNC | O_CREAT);
		else
			out = open(node->cmd_stdout_file, O_APPEND | O_WRONLY);
		dup2(out, STDOUT_FILENO);
		close(out);
	}
}

void	launch_process(t_ast_node *node, t_env *env)
{
	char	**args;
	int		ret;

	args = build_argv(node);
	if (strncmp(node->cmd_name, "echo", 5) == 0)
		exit(sh_echo(node));
	else if (strncmp(node->cmd_name, "env", 4) == 0)
		exit(sh_env(env));
	else if (strncmp(node->cmd_name, "pwd", 4) == 0)
		exit(sh_pwd());
	else if (strncmp(node->cmd_name, "cd", 3) == 0)
		exit(sh_cd(node, env));
	else if (strncmp(node->cmd_name, "exit", 5) == 0)
		exit(sh_exit(node));
	else
	{
		if (!get_exec_path_from_env(args[0], env))
		{
			ft_printf_fd(STDERR_FILENO, "minishell: %s: command not found\n",
				args[0]);
			exit(127);
		}
		ret = execve(get_exec_path_from_env(args[0], env), args,
				env_to_envp_format(env));
		if (ret == -1)
			ft_printf_fd(STDERR_FILENO, "minishell: %s: %s\n", args[0],
				strerror(errno));
	}
	exit(1);
}

char	**build_argv(t_ast_node *node)
{
	char	**args;

	args = malloc((node->cmd_arg_count + 2) * sizeof(char *));
	args[0] = node->cmd_name;
	for (int i = 0; i < node->cmd_arg_count; ++i)
	{
		args[i + 1] = node->cmd_args[i]->arg_value;
	}
	args[node->cmd_arg_count + 1] = NULL;
	return (args);
}
