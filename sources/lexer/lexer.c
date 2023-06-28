/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfernand <sfernand@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:57:49 by evmorvan          #+#    #+#             */
/*   Updated: 2023/06/28 10:44:14 by sfernand         ###   ########.fr       */
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

void	free_token(t_token *token)
{
	t_token *temp;

	temp = token;
	while (temp->next != NULL)
	{
		ft_printf("%s\n", temp->token);
		free(temp);
		temp = temp->next;
	}
	ft_printf("%s\n", temp->token);
	free(temp);
}

void	lexer(char *line)
{
	t_token	*token;
	int		i;
	char 	**argv;

	i = 1;
	argv = ft_split(line, ' ');
	token = malloc(sizeof(*token) * 2);
	if (!token)
		exit (EXIT_FAILURE);
	token->token = argv[0];
	token->next = NULL;
	while (argv[i])
	{
		add_token(token, argv[i]);
		i++;
	}
	free_token(token);
}
