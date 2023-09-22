/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:10:56 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/22 08:57:19 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit(void)
{
	ft_printf("exit\n");
	exit(0);
}

t_env	*initialize_env(char **envp)
{
	t_env	*env;
	t_env	*tmp;

	env = NULL;
	if (envp[0])
		env = env_from_parent(envp);
	else
	{
		tmp = malloc(sizeof(t_env));
		if (!tmp)
			return (NULL);
		tmp->key = "SHLVL";
		tmp->value = "1";
		tmp->is_secret = 0;
		tmp->next = env;
		tmp->prev = NULL;
		env = tmp;
	}
	env_set(env, "?", "0");
	env_set_secret(env, "?");
	return (env);
}

int	shell_pipeline(char *line, t_env *env)
{
	t_token		*tokens;
	t_ast_node	*cmds;
	char		*tmp;

	tmp = ft_strdup(line);
	tokens = lexer(line);
	if (!tokens->token)
		return (1);
	add_history(tmp);
	free(tmp);
	expand_tokens(env, tokens);
	interpret_quotes_tokens(tokens);
	cmds = parser(tokens, env);
	executor(cmds, env);
	free_all_nodes(cmds);
	return (0);
}

void	shell_loop(t_env *env)
{
	char	*line;
	int		i;

	while (TRUE)
	{
		initialize_signal();
		line = readline(PROMPT);
		if (line && line[0] != '\0')
		{
			i = 0;
			while (line[i] == ' ' || line[i] == '\t')
				i++;
			if (line[i] == '\0')
			{
				free(line);
				continue ;
			}
			line = ft_strdup(line + i);
			shell_pipeline(line, env);
		}
		if (!line)
			ft_exit();
		free(line);
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
	return (0);
}
