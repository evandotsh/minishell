/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:10:56 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/13 16:59:01 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_token(t_token *token)
{
	printf("\n[");
	while (token != NULL)
	{
		printf("*%s,", token->token);
		token = token->next;
	}
	printf("]\n");
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_token		*token;
	t_ast_node	*cmds;
	t_env		*env;
	int			debug;

	debug = 0;
	if (argc == 2 && strcmp(argv[1], "--debug") == 0)
		debug = 1;
	env = env_from_parent(envp);
	while (TRUE)
	{
		printf("\n%sminishell$ \n%s", C_PURPLE, C_YELLOW);
		line = readline(PROMPT C_RESET);
		add_history(line);
		if (line != NULL && line[0] != '\0')
		{
			token = lexer(line);
			cmds = parser(token);
			if (debug)
			{
				print_token(token);
				print_ast_node(cmds, 0);
			}
			expander(cmds, env);
			executor(cmds, env);
			free_all_nodes(cmds);
		}
		if (line == NULL)
		{
			ft_printf("exit\n");
			free(line);
			exit(0);
		}
	}
	free(line);
	return (0);
}
