/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 10:59:11 by evmorvan          #+#    #+#             */
/*   Updated: 2023/06/23 16:18:46 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*make_prompt(void)
{
	char	*pretty_cwd;
	char	*prompt;
	int		ret;

	pretty_cwd = get_pretty_cwd();
	ret = system("make -q");
	if (ret == 0)
		prompt = ft_strjoin(pretty_cwd, " " C_GREEN "✓" C_RESET " ");
	else
		prompt = ft_strjoin(pretty_cwd, " " C_RED "X" C_RESET " ");
	return (prompt);
}


int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_env	*env;

	(void)argc;
	(void)argv;
	env = ft_env(envp);
	(void) env;
	while (TRUE)
	{
		printf("\n%s%s\n%s", C_PURPLE, make_prompt(), C_YELLOW);
		line = readline(PROMPT C_RESET);
		if (line[0] != '\0')
			add_history(line);
		parser(line);
		//if (ft_strncmp(line, "debug", ft_strlen("debug")) == 0)
		//	debug(line, env);
		//else if (ft_strncmp(line, "exit", ft_strlen("exit")) == 0)
		//	break ;
		//else if (ft_strncmp(line, "clear", ft_strlen("clear")) == 0)
		//	system("clear");
		free(line);
	}
	free(line);
	return (0);
}
