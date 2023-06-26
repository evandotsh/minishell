/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfernand <sfernand@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:57:49 by evmorvan          #+#    #+#             */
/*   Updated: 2023/06/26 15:19:37 by sfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_token(t_token *token, char *str)
{
	t_token *new_token;

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

void	lexer(char *line)
{
	t_token	*token;
	int		i;
	char 	**argv;

	i = 0;
	argv = ft_split(line, " ");
	token = malloc(sizeof(*token) * 2);
	if (!token)
		exit (EXIT_FAILURE);
	token->token = argv[i];
	token->next = NULL;
	while (argv[++i])
	{
		add_token(token, argv[i]);
		i++;
	}
}
