/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:56:28 by evmorvan          #+#    #+#             */
/*   Updated: 2023/06/23 18:10:22 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	executor(t_cmd *cmd_list)
{
	t_cmd	cmd;
	int		pid;

	cmd = *cmd_list;
	pid = fork();
	if (pid == 0)
	{
		execve(cmd.cmd, cmd.args, NULL);
		sleep(1);
	}
	else
		waitpid(pid, NULL, 0);
}
