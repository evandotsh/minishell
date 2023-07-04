/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 10:59:11 by evmorvan          #+#    #+#             */
/*   Updated: 2023/06/29 12:04:50 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_minishell	g_minishell;

char	*make_prompt(void)
{
	char	*pretty_cwd;
	char	*prompt;

	pretty_cwd = get_pretty_cwd();
	if (g_minishell.last_exit_status)
		prompt = ft_strjoin(pretty_cwd, " " C_GREEN "✓" C_RESET " ");
	else
		prompt = ft_strjoin(pretty_cwd, " " C_RED "X" C_RESET " ");
	return (prompt);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_env	*env;
	t_token	*token;

	(void)argc;
	(void)argv;
	env = ft_env(envp);
	g_minishell.last_exit_status = 1;
	while (TRUE)
	{
		printf("\n%s%s\n%s", C_PURPLE, make_prompt(), C_YELLOW);
		line = readline(PROMPT C_RESET);
		token = lexer(line);
		while (token != NULL)
		{
			printf("%s\n", token->token);
			token = token->next;
		}
		if (line[0] != '\0')
			add_history(line);
		if (ft_strncmp(line, "debug", ft_strlen("debug")) == 0)
			debug(line, env);
		else if (ft_strncmp(line, "exit", ft_strlen("exit")) == 0)
			break ;
		else if (ft_strncmp(line, "clear", ft_strlen("clear")) == 0)
			system("clear");
		else
			//parser(line);
		free(line);
	}
	free(line);
	return (0);
}
