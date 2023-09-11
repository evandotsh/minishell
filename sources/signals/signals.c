/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:24:09 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/06 14:32:01 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void sh_sigint(int sig)
{
    (void)sig;
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void sh_sigquit(int sig)
{
    (void)sig;
    printf("Quit: 3\n");
}

void sh_signals(t_node *node)
{
    signal(SIGINT, sh_sigint);
    signal(SIGQUIT, sh_sigquit);
}