/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 20:00:37 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/25 12:54:25 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	heredoc_loop(t_env *env, char *delim, int fd)
{
	char	*tmp;
	char	*line;

	while (1)
	{
		line = readline("> ");
		tmp = expand(env, line);
		free(line);
		if (ft_strcmp(tmp, delim) == 0)
		{
			free(delim);
			free(tmp);
			break ;
		}
		write(fd, tmp, ft_strlen(tmp));
		write(fd, "\n", 1);
		free(tmp);
	}
}

char	*handle_heredoc(t_env *env, t_token *tokens)
{
	char	*delim;
	char	*result;
	int		fd;
	char	*random;

	random = ft_itoa(ft_random());
	result = ft_strjoin("/tmp/heredoc", random);
	free(random);
	delim = ft_strdup(tokens->token);
	fd = open(result, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		free(result);
		free(delim);
		perror("open");
		return (NULL);
	}
	heredoc_loop(env, delim, fd);
	close(fd);
	return (result);
}
