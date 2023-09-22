/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:52:47 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/22 08:16:25 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_all_tokens(t_token *token)
{
	t_token	*tmp;

	while (token != NULL)
	{
		tmp = token;
		token = token->next;
		free(tmp->token);
		free(tmp);
	}
}

void	free_all_nodes(t_ast_node *nodes)
{
	if (nodes == NULL)
		return ;
	if (nodes->type == ND_CMD)
	{
		free(nodes->cmd_name);
		while (nodes->cmd_arg_count > 0)
		{
			free_all_nodes(nodes->cmd_args[nodes->cmd_arg_count - 1]);
			nodes->cmd_arg_count--;
		}
		free(nodes->cmd_args);
		free(nodes->cmd_stdin_file);
		free(nodes->cmd_stdout_file);
	}
	else if (nodes->type == ND_PIPE)
	{
		free_all_nodes(nodes->pipe_lhs);
		free_all_nodes(nodes->pipe_rhs);
	}
	else if (nodes->type == ND_ARG)
		free(nodes->arg_value);
	free(nodes);
}

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	new_ptr = malloc(size);
	if (!new_ptr)
		return (NULL);
	if (ptr)
	{
		ft_memcpy(new_ptr, ptr, size);
		free(ptr);
	}
	return (new_ptr);
}
