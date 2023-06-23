/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 18:58:13 by evmorvan          #+#    #+#             */
/*   Updated: 2023/06/23 15:37:02 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	colors(void)
{
	printf(C_RESET DEBUG_PANGRAM);
	printf(C_RED DEBUG_PANGRAM);
	printf(C_GREEN DEBUG_PANGRAM);
	printf(C_YELLOW DEBUG_PANGRAM);
	printf(C_BLUE DEBUG_PANGRAM);
	printf(C_PURPLE DEBUG_PANGRAM);
	printf(C_CYAN DEBUG_PANGRAM);
}

// echo "hello world" > file.txt
void	example_cmd_struct(void)
{
	t_cmd	cmd;
	t_redir	redir;

	redir.type = REDIR_OUT;
	redir.file = "file.txt";
	cmd.cmd = "/bin/echo";
	cmd.args = ft_split("echo hello world", ' ');
	cmd.redir = &redir;
	cmd.next = NULL;
	printf("cmd: %s\n", cmd.cmd);
	printf("args: %s %s\n", cmd.args[0], cmd.args[1]);
	printf("redir_type: %d\n", cmd.redir->type);
	printf("redir_file: %s\n", cmd.redir->file);
	printf("next: %p\n", cmd.next);
	executor(&cmd);
}

void	debug(char *line, t_env *env)
{
	char	**args;

	args = ft_split(line, ' ');
	if (ft_strncmp(args[1], "colors", ft_strlen("colors")) == 0)
		colors();
	if (ft_strncmp(args[1], "env", ft_strlen("env")) == 0)
		print_env(env);
	if (ft_strncmp(args[1], "leaks", ft_strlen("leaks")) == 0)
		system("leaks minishell");
	if (ft_strncmp(args[1], "run", ft_strlen("run")) == 0)
		system(args[2]);
	if (ft_strncmp(args[1], "cmd", ft_strlen("cmd")) == 0)
		example_cmd_struct();
}
