/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:24:09 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/26 11:53:40 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		g_signal = 0;

void	handle_sigint(int sig)
{
	if (g_signal == 0)
		return ;
	//rl_replace_line("", 0);
	rl_on_new_line();
	if (g_signal == sig)
	{
		printf("\n");
		rl_redisplay();
	}
	g_signal = 0;
}

void	initialize_signal(void)
{
	signal(SIGINT, shell_sigint);
	signal(SIGQUIT, shell_sigquit);
	signal(SIGTERM, shell_sigterm);
}

void	shell_sigint(int sig)
{
	g_signal = sig;
	handle_sigint(sig);
}

void	shell_sigquit(int sig)
{
	g_signal = sig;
	rl_on_new_line();
	rl_redisplay();
	(void) sig;
}

void	shell_sigterm(int sig)
{
	g_signal = sig;
	rl_on_new_line();
	//rl_replace_line("", 0);
	rl_redisplay();
	(void) sig;
}
