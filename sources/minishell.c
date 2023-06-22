/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 10:59:11 by evmorvan          #+#    #+#             */
/*   Updated: 2023/06/22 11:18:29 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv)
{
	char	*line;
	t_env	*env;

	(void)argc;
	(void)argv;
	(void)env;
	env = NULL;
	while (TRUE)
	{
		line = readline(PROMPT);
		if (!line)
			break ;
		if (line[0] != '\0')
			add_history(line);
		if (ft_strncmp(line, "exit", ft_strlen(line)) == 0)
			break ;
		printf("%s\n", line);
		free(line);
	}
	free(line);
	return (0);
}
