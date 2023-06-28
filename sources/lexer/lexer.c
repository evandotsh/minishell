/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfernand <sfernand@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:57:49 by evmorvan          #+#    #+#             */
/*   Updated: 2023/06/28 17:10:41 by sfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_token(t_token *token, char *str)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		exit(EXIT_FAILURE);
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
		if (str[i] == '|' || (str[i] == '>' && str[i - 1] != '>')
			|| (str[i] == '<' && str[i - 1] != '<'))
		{
			result[j++] = ' ';
			if (str[i + 2] == '>' || str[i + 2] == '<')
			{
				ft_printf("syntax error\n");
				return (NULL);
			}
		}
		if (str[i - 1] == '|' || (str[i - 1] == '>' && str[i] != '>')
			|| (str[i - 1] == '<' && str[i] != '<'))
			result[j++] = ' ';
		result[j++] = str[i++];
	}
	result[j] = '\0';
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
	if (str == NULL)
		return (NULL);
	result = (char *)malloc((len * 2 + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	result = check_redir(str, i, j, result);
	return (result);
}

t_token	*lexer(char *line)
{
	t_token	*token;
	int		i;
	char	**argv;

	i = 1;
	line = add_spaces(line);
	token = malloc(sizeof(*token) * 2);
	if (line == NULL)
	{
		token->token = NULL;
		token->next = NULL;
		return (token);
	}
	argv = ft_split_lexer(line, ' ');
	if (!token)
		exit (EXIT_FAILURE);
	token->token = argv[0];
	token->next = NULL;
	while (argv[i])
	{
		add_token(token, argv[i]);
		i++;
	}
	free(line);
	return (token);
}
