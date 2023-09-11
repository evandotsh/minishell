/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 07:00:33 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/11 12:27:47 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_node_arg(t_ast_node *node, int index)
{
	if (node->type == ND_CMD)
	{
		if (index < node->cmd_arg_count)
			return (node->cmd_args[index]->arg_value);
	}
	return (NULL);
}

int	get_node_arg_count(t_ast_node *node)
{
	if (node->type == ND_CMD)
		return (node->cmd_arg_count);
	return (0);
}
