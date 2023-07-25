/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfernand <sfernand@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:58:01 by evmorvan          #+#    #+#             */
/*   Updated: 2023/07/22 12:52:48 by sfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*add_args(t_token *token)
{
	t_cmd		*new_args;
	int			i;
	
	i = 0;
	new_args = malloc(sizeof(*new_args));
	new_args->args = malloc(sizeof(char *));
	new_args->cmd = malloc(sizeof(char *));
	new_args->cmd = NULL;
	new_args->redir = NULL;
	new_args->next = NULL;
	while (token->next != NULL)
	{
		if (new_args->cmd == NULL)
			new_args->cmd = ft_strdup(token->token);
		else if (token->token[0] == '|'
		|| token->token[0] == '<' || token->token[0] == '>')
			return (add_redir(token->token, new_args, token), new_args);
		else if (token->token[0] != 0)
		{
			new_args->args[i] = ft_strdup(token->token);
			i++;
		}
		if (token->next)
			token = token->next;
	}
	if (new_args->cmd == NULL)
	{
		new_args->cmd = ft_strdup(token->token);
		if (token->next != NULL)
			token = token->next;
	}
	else if (token->token[0] == '|'
	|| token->token[0] == '<' || token->token[0] == '>')
		add_redir(token->token, new_args, token);
	else if (token->token[0] != 0)
	{
		new_args->args[i] = ft_strdup(token->token);
	}
	return (new_args);
}

void	parser(t_token *token)
{
	t_cmd	*cmd;
	int	i;

	i = 0;
	cmd = malloc(sizeof(*cmd));
	cmd->cmd = "test";
	cmd->next = NULL;
	cmd->next = add_args(token);
	cmd = cmd->next;
}
