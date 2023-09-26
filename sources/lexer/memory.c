/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:52:47 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/26 09:51:47 by evmorvan         ###   ########.fr       */
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

void	*ft_memcpy(void *dst, void const *src, size_t n)
{
	unsigned char	*dst_c;
	unsigned char	*src_c;

	if (!dst && !src)
		return (NULL);
	if (dst == src || n == 0)
		return (dst);
	dst_c = (unsigned char *)dst;
	src_c = (unsigned char *)src;
	while (n--)
		*dst_c++ = *src_c++;
	return (dst);
}

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (!ptr)
		return (malloc(new_size));
	if (new_size <= old_size)
		return (ptr);
	new_ptr = malloc(new_size);
	if (!new_ptr)
	{
		free(ptr);
		return (NULL);
	}
	ft_memcpy(new_ptr, ptr, old_size);
	free(ptr);
	return (new_ptr);
}
