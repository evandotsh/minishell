/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:24:09 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/19 16:19:20 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// I need to setup a signal handlers which handles SIGINT and SIGQUIT,
// the main function is called with a node which is the root of the AST
// and contains a cmd_pid which is the pid of the command which is currently
// running, if the pid is 0, it means that the command is not running.

// I can only use one global variable which is the number of the signal received

int	g_signal = 0;

void	shell_sigint(int sig)
{
	(void) sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	shell_sigquit(int sig)
{
	(void) sig;
	printf("\nexit");
	exit(0);
}

void	shell_sigterm(int sig)
{
	(void) sig;
}
