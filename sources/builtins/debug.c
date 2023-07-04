/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 18:58:13 by evmorvan          #+#    #+#             */
/*   Updated: 2023/07/03 17:26:27 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// cat STRUCTS.md | grep minishell | wc -c
void	pipeline_test(void)
{
	t_redir	*redir;
	t_cmd	*pipeline;

	pipeline = malloc(sizeof(t_cmd) * 3);
	redir = malloc(sizeof(t_redir) * 3);
	redir[0].type = REDIR_PIPE;
	redir[1].type = REDIR_PIPE;
	redir[2].type = REDIR_NONE;
	pipeline[0].cmd = "/bin/cat";
	pipeline[0].args = ft_split("/bin/cat STRUCTS.md", ' ');
	pipeline[0].redir = &redir[0];
	pipeline[0].next = &pipeline[1];
	pipeline[1].cmd = "/usr/bin/grep";
	pipeline[1].args = ft_split("/usr/bin/grep minishell", ' ');
	pipeline[1].redir = &redir[1];
	pipeline[1].next = &pipeline[2];
	pipeline[2].cmd = "/usr/bin/wc";
	pipeline[2].args = ft_split("/usr/bin/wc -c", ' ');
	pipeline[2].redir = &redir[2];
	pipeline[2].next = NULL;
	executor(pipeline);
}

void	redir_out_test(void)
{
	t_redir	*redir;
	t_cmd	*pipeline;

	pipeline = malloc(sizeof(t_cmd));
	redir = malloc(sizeof(t_redir));
	redir->type = REDIR_OUT;
	redir->file = "test.txt";
	pipeline->cmd = "/bin/cat";
	pipeline->args = ft_split("/bin/cat STRUCTS.md", ' ');
	pipeline->redir = redir;
	pipeline->next = NULL;
	executor(pipeline);
}

void	redir_in_test(void)
{
	t_redir	*redir;
	t_cmd	*pipeline;

	pipeline = malloc(sizeof(t_cmd));
	redir = malloc(sizeof(t_redir));
	redir->type = REDIR_IN;
	redir->file = "STRUCTS.md";
	pipeline->cmd = "/bin/cat";
	pipeline->args = ft_split("/bin/cat", ' ');
	pipeline->redir = redir;
	pipeline->next = NULL;
	executor(pipeline);
}

void	expander_test(void)
{
	t_cmd	*pipeline;
	int		i;

	i = 0;
	pipeline = malloc(sizeof(t_cmd));
	pipeline->cmd = "/bin/echo";
	pipeline->args = ft_split("/bin/echo $HOME", ' ');
	pipeline->redir = NULL;
	pipeline->next = NULL;
	printf("before:\n");
	while (pipeline->args[i] != NULL)
	{
		printf("%s\n", pipeline->args[i]);
		i++;
	}
	expander(pipeline);
	printf("after:\n");
	i = 0;
	while (pipeline->args[i] != NULL)
	{
		printf("%s\n", pipeline->args[i]);
		i++;
	}
}

void	debug(char *line, t_env *env)
{
	char	**args;

	args = ft_split(line, ' ');
	if (ft_strncmp(args[1], "colors", ft_strlen("colors")) == 0)
	{
		printf(C_RED DEBUG_PANGRAM);
		printf(C_GREEN DEBUG_PANGRAM);
		printf(C_YELLOW DEBUG_PANGRAM);
		printf(C_BLUE DEBUG_PANGRAM);
		printf(C_PURPLE DEBUG_PANGRAM);
		printf(C_CYAN DEBUG_PANGRAM);
		printf(C_RESET DEBUG_PANGRAM);
	}
	if (ft_strncmp(args[1], "env", ft_strlen("env")) == 0)
		print_env(env);
	if (ft_strncmp(args[1], "leaks", ft_strlen("leaks")) == 0)
		system("leaks minishell");
	if (ft_strncmp(args[1], "run", ft_strlen("run")) == 0)
		system(args[2]);
	if (ft_strncmp(args[1], "cmd", ft_strlen("cmd")) == 0)
		pipeline_test();
	if (ft_strncmp(args[1], "lexer", ft_strlen("lexer")) == 0)
		lexer(line + ft_strlen(args[0]) + ft_strlen(args[1]) + 2);
	if (ft_strncmp(args[1], "expander", ft_strlen("expander")) == 0)
		expander_test();
}
