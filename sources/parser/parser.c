/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:58:01 by evmorvan          #+#    #+#             */
/*   Updated: 2023/06/23 18:09:32 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// dumb parser, only handle one command, no pipes, no redirections, no nothing
void	parser(char *line)
{
	t_cmd	cmd;
	int		i;
	int		j;

	i = 0;
	j = 0;
	cmd.cmd = NULL;
	cmd.args = NULL;
	while (line[i] != '\0')
	{
		if (line[i] == ' ')
		{
			if (cmd.cmd == NULL)
				cmd.cmd = ft_strndup(line, i);
			else
			{
				cmd.args = malloc(sizeof(char *) * 3);
				cmd.args[0] = ft_strdup(cmd.cmd);
				cmd.args[1] = ft_strndup(line, i);
				cmd.args[2] = NULL;
			}
			j = i + 1;
		}
		i++;
	}
	if (cmd.cmd == NULL)
		cmd.cmd = ft_strndup(line, i);
	else
	{
		cmd.args = malloc(sizeof(char *) * 3);
		cmd.args[0] = ft_strdup(cmd.cmd);
		cmd.args[1] = ft_strndup(line + j, i - j);
		cmd.args[2] = NULL;
	}
	executor(&cmd);
	free(cmd.cmd);
	free(cmd.args[0]);
	free(cmd.args);
}
