/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfernand <sfernand@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 12:38:01 by sfernand          #+#    #+#             */
/*   Updated: 2023/07/22 14:24:51 by sfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_redir(char	*str, t_cmd *new_args, t_token *token)
{
	t_redir	*redir;

	redir = malloc(sizeof(*redir) * 3);
	redir->file = ft_strdup(str);
	redir->next = NULL;
	if (str[0] == '|')
	{
		redir->file = NULL;
		redir->type = REDIR_PIPE;
		if (token->next)
				token = token->next;
		new_args->next = add_args(token);
	}
	else if (str[0] == '<')
	{
		token = token->next;
		if (ft_strncmp(str, "<<", 2) == 0)
		{
			redir->file = ft_strdup(token->token);
			redir->type = REDIR_HEREDOC;
			if (token->next)
				token = token->next;
		}
		else
		{
			redir->file = ft_strdup(token->token);
			redir->type = REDIR_IN;
			if (token->next)
				token = token->next;
		}
	}
	else if (str[0] == '>')
	{
		token = token->next;
		if (ft_strncmp(str, ">>", 2) == 0)
		{
			redir->file = ft_strdup(token->token);
			redir->type = REDIR_APPEND;
			if (token->next)
				token = token->next;
		}
		else
		{
			redir->file = ft_strdup(token->token);
			redir->type = REDIR_OUT;
			if (token->next)
				token = token->next;
		}
	}
	new_args->redir = redir;
}