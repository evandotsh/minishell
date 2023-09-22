/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:11:28 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/22 08:20:57 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_indent(int depth)
{
	while (depth > 0)
	{
		printf("  ");
		depth--;
	}
}

void	print_cmd_node(t_ast_node *node, int depth)
{
	int	i;

	printf("CMD(name=%s, argc=%d)\n", node->cmd_name, node->cmd_arg_count);
	i = 0;
	while (i < node->cmd_arg_count)
	{
		print_ast_node(node->cmd_args[i], depth + 1);
		i++;
	}
	if (node->cmd_stdin_source)
	{
		print_indent(depth);
		printf("Input source: %s\n", node->cmd_stdin_file);
	}
	if (node->cmd_stdout_dest)
	{
		print_indent(depth);
		printf("Output destination: %s\n", node->cmd_stdout_file);
	}
}

void	print_arg_node(t_ast_node *node)
{
	printf("ARG(value=%s)\n", node->arg_value);
}

void	print_pipe_node(t_ast_node *node, int depth)
{
	printf("\n");
	print_ast_node(node->pipe_lhs, depth + 1);
	print_indent(depth + 1);
	printf("| PIPE\n");
	print_ast_node(node->pipe_rhs, depth + 1);
}

void	print_ast_node(t_ast_node *node, int depth)
{
	if (node == NULL)
		return ;
	print_indent(depth);
	if (node->type == ND_CMD)
	{
		printf("CMD");
		print_cmd_node(node, depth);
	}
	else if (node->type == ND_ARG)
	{
		printf("ARG");
		print_arg_node(node);
	}
	else if (node->type == ND_PIPE)
	{
		printf("PIPE");
		print_pipe_node(node, depth);
	}
	else
		printf("UNKNOWN");
}
