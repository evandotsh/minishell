/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:56:28 by evmorvan          #+#    #+#             */
/*   Updated: 2023/06/26 17:06:34 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
t_redir	*redir;
t_cmd	*pipeline;

pipeline = malloc(sizeof(t_cmd));
redir = malloc(sizeof(t_redir) * 2);
redir[0].type = REDIR_PIPE;
redir[1].type = REDIR_NONE;
pipeline[0].cmd = "/bin/cat";
pipeline[0].args = ft_split("/bin/cat STRUCTS.md", ' ');
pipeline[0].redir = &redir[0];
pipeline[0].next = &pipeline[1];
pipeline[1].cmd = "/usr/bin/grep";
pipeline[1].args = ft_split("/usr/bin/grep minishell", ' ');
pipeline[1].redir = &redir[1];
pipeline[1].next = NULL;
*/

// We need to restore stdin and stdout after the pipeline is done
// so we can continue to use the shell normally
void	executor(t_cmd *pipeline)
{
	int		fd[2];
	int		stdin_copy;
	int		stdout_copy;
	t_cmd	*cmd;
	int		pid;

	stdin_copy = dup(STDIN_FILENO);
	stdout_copy = dup(STDOUT_FILENO);
	while (pipeline)
	{
		if (pipeline->redir->type == REDIR_PIPE)
		{
			pipe(fd);
			pid = fork();
			if (pid == -1)
			{
				return ;
			}
			else if (pid == 0)
			{
				// Child process
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
				close(fd[1]);
				execve(pipeline->cmd, pipeline->args, NULL);
				_exit(1);
			}
			else
			{
				// Parent process
				dup2(fd[0], STDIN_FILENO);
				close(fd[0]);
				close(fd[1]);
			}
		}
		else if (pipeline->redir->type == REDIR_OUT)
		{
			fd[1] = open(pipeline->redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
		}
		else if (pipeline->redir->type == REDIR_APPEND)
		{
			fd[1] = open(pipeline->redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
		}
		else if (pipeline->redir->type == REDIR_HEREDOC)
		{
			fd[1] = open(pipeline->redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
		}
		else if (pipeline->redir->type == REDIR_IN)
		{
			fd[0] = open(pipeline->redir->file, O_RDONLY);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
		}
		cmd = pipeline;
		pid = fork();
		if (pid == -1)
		{
			return ;
		}
		else if (pid == 0)
		{
			// Child process
			execve(cmd->cmd, cmd->args, NULL);
			_exit(1);  // Exit child process if execve fails
		}
		else
		{
			// Parent process
			waitpid(pid, NULL, 0);
		}

		pipeline = pipeline->next;
	}

	dup2(stdin_copy, STDIN_FILENO);
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdin_copy);
	close(stdout_copy);
}