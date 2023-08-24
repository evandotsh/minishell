/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 06:43:32 by evmorvan          #+#    #+#             */
/*   Updated: 2023/08/24 16:39:03 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void executor(t_ast_node *node, t_env *env)
{
	int		pid;
	int		ret;
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;
	char	**args;
	int		i;
	int		in;
	int		out;

	if (node == NULL)
		return;

	if (node->type == ND_CMD)
	{
		if (ft_strncmp(node->cmd_name, "unset", 5) == 0)
			sh_unset(node, env);
		pid = fork();

		if (pid == 0)
		{
			args = malloc((node->cmd_arg_count + 2) * sizeof *args);
			args[0] = node->cmd_name;
			for(i = 0; i < node->cmd_arg_count; ++i) {
				args[i + 1] = node->cmd_args[i]->arg_value;
			}
			args[i + 1] = NULL;

			if (node->cmd_stdin_file)
			{
				in = open(node->cmd_stdin_file, O_RDONLY);
				dup2(in, STDIN_FILENO);
				close(in);
			}

			if (node->cmd_stdout_file)
			{
				if (node->cmd_stdout_dest == 1) {
					out = open(node->cmd_stdout_file, O_WRONLY | O_TRUNC | O_CREAT);
				} else {
					out = open(node->cmd_stdout_file, O_APPEND | O_WRONLY);
				}
				dup2(out, STDOUT_FILENO);
				close(out);
			}
			//builtins
			if (ft_strncmp(node->cmd_name, "echo", 4) == 0)
				sh_echo(node);
			else if (ft_strncmp(node->cmd_name, "env", 3) == 0)
				sh_env(env);
			else if (ft_strncmp(node->cmd_name, "pwd", 3) == 0)
				sh_pwd();
			//else if (ft_strncmp(node->cmd_name, "export", 6) == 0)
			//	sh_export(node, env);
			//else if (ft_strncmp(node->cmd_name, "cd", 2) == 0)
			//	sh_cd(node, env);
			//else if (ft_strncmp(node->cmd_name, "exit", 4) == 0)
			//	sh_exit(node);
			else
			{
				execve(get_exec_path_from_env(args[0], env), args, env_to_envp_format(env));
				perror("execve");
				exit(EXIT_FAILURE);
			}
		} else {
			waitpid(pid, &ret, 0);
		}
	}
	else if (node->type == ND_PIPE)
	{
		if (pipe(pipefd) < 0) {
			fprintf(stderr, "Pipe failed. \n");
			return;
		}
		pid1 = fork();
		if (pid1 < 0) {
			fprintf(stderr, "Fork failed. \n");
			return;
		}
		if (pid1 == 0) {
			close(pipefd[0]);
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);

			executor(node->pipe_lhs, env);
			exit(0);
		} 
		else {
			pid2 = fork();
			if (pid2 < 0) {
				fprintf(stderr, "Fork failed. \n");
				return;
			}
			if (pid2 == 0 ) {
				close(pipefd[1]);
				dup2(pipefd[0], STDIN_FILENO);
				close(pipefd[0]);

				executor(node->pipe_rhs, env);
				exit(0);
			} else {
				close(pipefd[0]);
				close(pipefd[1]);
				wait(NULL);
				wait(NULL);
			}
		}
	}
}
