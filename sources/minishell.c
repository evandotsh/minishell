/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:10:56 by evmorvan          #+#    #+#             */
/*   Updated: 2023/10/02 13:05:20 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit(t_env *env)
{
	free_all_env(env);
	ft_printf("exit\n");
	exit(0);
}

int	shell_pipeline(char *line, t_env *env)
{
	t_token		*tokens;
	t_ast_node	*cmds;
	char		*tmp;

	tmp = ft_strdup(line);
	tokens = lexer(line);
	if (!tokens->token)
	{
		free_all_tokens(tokens);
		free(tmp);
		return (1);
	}
	add_history(tmp);
	free(tmp);
	dequotter2000(tokens);
	expand_tokens(tokens, env);
	cmds = parser(tokens, env);
	free_all_tokens(tokens);
	executor(cmds, env);
	free_all_nodes(cmds);
	return (0);
}

int	execute_prompt(char *line, t_env *env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\0')
	{
		free(line);
		return (1);
	}
	tmp = ft_strdup(line + i);
	free(line);
	shell_pipeline(tmp, env);
	return (0);
}

void	shell_loop(t_env *env)
{
	char	*line;

	while (TRUE)
	{
		initialize_signal();
		line = readline(PROMPT);
		if (line && line[0] != '\0')
		{
			if (execute_prompt(line, env) == 1)
				continue ;
		}
		else if (line && ft_strlen(line) == 0)
			free(line);
		else if (!line)
		{
			free(line);
			ft_exit(env);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env		*env;

	(void)argc;
	(void)argv;
	env = initialize_env(envp);
	echo_control_seq(0);
	shell_loop(env);
	free_all_env(env);
	return (0);
}
