/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfernand <sfernand@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:58:01 by evmorvan          #+#    #+#             */
/*   Updated: 2023/08/07 14:28:54 by sfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	add_args2(t_token *token, t_cmd *new_args, int i)
{
	if (new_args->cmd == NULL)
		new_args->cmd = ft_strdup(token->token);
	else if (token->token[0] == '|'
		|| token->token[0] == '<' || token->token[0] == '>')
		add_redir(token->token, new_args, token->next);
	else if (token->token[0] != 0)
	{
		new_args->args[i] = ft_strdup(token->token);
		i++;
	}
	return (i);
}

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
		i = add_args2(token, new_args, i);
		if (token->next)
			token = token->next;
	}
	if (token->token[0] == '|'
		|| token->token[0] == '<' || token->token[0] == '>')
		return (add_redir(token->token, new_args, token->next), new_args);
	else 
		i = add_args2(token, new_args, i);
	return (new_args);
}

void	parser(t_token *token)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = malloc(sizeof(*cmd));
	cmd->cmd = "test";
	cmd->next = NULL;
	cmd->next = add_args(token);
	cmd = cmd->next;
	ft_printf("%s\n", cmd->cmd);
	cmd = cmd->next;
	ft_printf("%s\n", cmd->cmd);
}
