/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:57:49 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/19 09:00:19 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_token(t_token *token, char *str)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
	{
		free(new_token);
		exit(EXIT_FAILURE);
	}
	if (str[0] == 0)
		return ;
	new_token->token = str;
	new_token->next = NULL;
	while (token->next != NULL)
	{
		if (token->next != NULL)
			token = token->next;
	}
	token->next = new_token;
}

char	*check_redir(char *str, int i, int j, char *result)
{
	while (str[i] != '\0')
	{
		if (str[i] == 34 || str[i] == 39)
			quote(str, i, j, result);
		if (((str[i] == '|' && str[i - 1] != '|') || (str[i] == '>'
					&& str[i - 1] != '>') || (str[i] == '<'
					&& str[i - 1] != '<'))
			&& (str[i - 1] != 34 && str[i - 1] != 39))
		{
			result[j++] = ' ';
			if (str[i + 2] == '>' || str[i + 2] == '<')
				return (free(str), NULL);
		}
		if (i > 0 && str[i] && str[i - 1] && str[i - 1] != '\0' && (
				(str[i - 1] == '|' && str[i] != '|') || 
				(str[i - 1] == '>' && str[i] != '>') || 
				(str[i - 1] == '<' && str[i] != '<')) && 
			(str[i - 1] != 34 && str[i - 1] != 39))
			result[j++] = ' ';
		result[j++] = str[i++];
	}
	result[j] = '\0';
	result = ft_strtrim_lexer(result);
	result = ft_epur_str(result);
	return (result);
}

char	*add_spaces(char *str)
{
	size_t	len;
	char	*result;
	size_t	i;
	size_t	j;

	len = ft_strlen(str);
	i = 0;
	j = 0;
	if (str == NULL || len == 0)
		return (free(str), NULL);
	result = (char *)malloc((len * 2 + 1) * sizeof(char));
	if (result == NULL)
	{
		free(str);
		return (NULL);
	}
	result = check_redir(str, i, j, result);
	free(str);
	return (result);
}

t_token	*lexer2(t_token *token, int i, char **argv)
{
	if (!argv)
	{
		token->token = NULL;
		token->next = NULL;
		free(argv);
		return (token);
	}
	token->token = argv[0];
	token->next = NULL;
	if (argv[1] != NULL)
	{
		while (argv[i++])
		{
			if (argv[i] != NULL)
				add_token(token, argv[i]);
		}
	}
	free(argv);
	return (token);
}

t_token	*lexer(char *line)
{
	t_token	*token;
	int		i;
	char	**argv;

	i = 0;
	line = ft_strtrim_lexer(line);
	line = ft_epur_str(line);
	line = add_spaces(line);
	if (line != NULL)
		line = ft_epur_str(line);
	token = malloc(sizeof(*token) * 2);
	if (!token)
	{
		free (line);
		exit (EXIT_FAILURE);
	}
	if (line == NULL)
	{
		token->token = NULL;
		token->next = NULL;
		return (token);
	}
	argv = ft_split_lexer(line, ' ');
	free(line);
	return (lexer2(token, i, argv));
}
