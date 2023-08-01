/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfernand <sfernand@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 12:38:01 by sfernand          #+#    #+#             */
/*   Updated: 2023/07/28 13:48:46 by sfernand         ###   ########.fr       */
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
		if (new_args->redir == NULL)
			new_args->redir = redir;
		else 
			new_args->redir->next = redir;
		new_args->next = add_args(token);
	}
	else if (str[0] == '<')
	{
		if (ft_strncmp(str, "<<", 2) == 0)
		{
			redir->file = ft_strdup(token->token);
			redir->type = REDIR_HEREDOC;
		}
		else
		{
			redir->file = ft_strdup(token->token);
			redir->type = REDIR_IN;
		}
		if (new_args->redir == NULL)
			new_args->redir = redir;
		else 
			new_args->redir->next = redir;
	}
	else if (str[0] == '>')
	{
		if (ft_strncmp(str, ">>", 2) == 0)
		{
			redir->file = token->token;
			redir->type = REDIR_APPEND;
		}
		else
		{
			redir->file = token->token;
			redir->type = REDIR_OUT;
		}
		if (new_args->redir == NULL)
			new_args->redir = redir;
		else 
			new_args->redir->next = redir;
	}
}