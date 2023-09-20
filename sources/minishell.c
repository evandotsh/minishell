/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfernand <sfernand@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:10:56 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/21 01:29:50 by sfernand         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../includes/minishell.h"

t_env	*initialize_env(char **envp)
{
	t_env	*env;

	env = env_from_parent(envp);
	env_set(env, "?", "0");
	env_set_secret(env, "?");
	return (env);
}

void	initialize_signal(void)
{
	signal(SIGINT, shell_sigint);
	signal(SIGQUIT, shell_sigquit);
	signal(SIGTERM, shell_sigterm);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_token		*token;
	t_ast_node	*cmds;
	t_env		*env;
	int			i;

	(void)argc;
	(void)argv;
	env = initialize_env(envp);
	initialize_signal();
	while (TRUE)
	{
		line = readline(PROMPT);
		add_history(line);
		if (line != NULL && line[0] != '\0')
		{
			i = 0;
			while (line[i] == ' ' || line[i] == '\t')
				i++;
			line = ft_strdup(line + i);
			token = lexer(line);
			if (token->token != NULL)
			{
				cmds = parser(token);
				free_all_tokens(token);
				expander(cmds, env);
				executor(cmds, env);
				free_all_nodes(cmds);
			}
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
