/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfernand <sfernand@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:58:01 by evmorvan          #+#    #+#             */
/*   Updated: 2023/07/10 00:00:55 by sfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_redir(char	*str, t_cmd *new_args, t_token *token)
{
	t_redir	*redir;

	ft_printf("rets6\n");
	redir = malloc(sizeof(*redir) * 3);
	ft_printf("rets7\n");
	redir->file = str;
	ft_printf("rets8\n");
	redir->next = NULL;
	ft_printf("rets9\n");
	ft_printf("rets10\n");
	if (!new_args->redir)
	{
		ft_printf("1\n");
		new_args->redir = redir;
		if (str[0] == '|')
		{
			if (token->next)
				token = token->next;
			add_args(new_args->next, token);
		}
	} 
	else if (new_args->redir)
	{
		ft_printf("2\n");
		new_args->redir->next = redir;
		if (str[0] == '|')
		{
			if (token->next)
				token = token->next;
			add_args(new_args->next, token);
		}
	}
	ft_printf("rets11\n");
}

void	add_args(t_cmd	*cmd, t_token *token)
{
	t_cmd		*new_args;
	int			i;
	
	i = 0;
	ft_printf("%s\n", token->token);
	ft_printf("rets1\n");
	new_args = malloc(sizeof(*new_args));
	ft_printf("rets2\n");
	ft_printf("rets3\n");
	ft_printf("rets4\n");
	new_args->args = malloc(sizeof(char *));
	new_args->next = NULL;
	ft_printf("rets5\n");
	while (token->next != NULL)
	{
		ft_printf("%s = token\n", token->token);
		if (new_args->cmd == NULL)
		{	
			ft_printf("CMD\n");
			new_args->cmd = token->token;
			ft_printf("cmd = %s\n", new_args->cmd);
		}
		else if (token->token[0] == '|'
		|| token->token[0] == '<' || token->token[0] == '>')
			add_redir(token->token, new_args, token);
		else if (token->token[0] != 0)
		{
			ft_printf("yrd1\n");
			new_args->args[i] = ft_strdup(token->token);
			ft_printf("yrd2\n");
			i++;
		}
		ft_printf("rets12\n");
		if (token->next)
			token = token->next;
	}
	ft_printf("rets13\n");
	if (new_args->cmd == NULL)
	{
		ft_printf("CMD\n");
		new_args->cmd = token->token;
		if (token->next != NULL)
			token = token->next;
	}
	else if (token->token[0] == '|'
	|| token->token[0] == '<' || token->token[0] == '>')
		add_redir(token->token, new_args, token);
	else if (token->token[0] != 0)
		new_args->args[i] = ft_strdup(token->token);
	cmd = new_args;
}

void	parser(t_token *token)
{
	t_cmd	*cmd;
	int	i;

	i = 0;
	cmd = malloc(sizeof(*cmd));
	cmd->next = NULL;
	ft_printf("cmd\n");
	if (token->next != NULL)
		add_args(cmd, token);
	ft_printf("cmd = %s\n", cmd->cmd);
}
