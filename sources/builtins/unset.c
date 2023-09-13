/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:26:37 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/13 16:08:05 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	sh_unset(t_ast_node *node, t_env *env)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (get_node_arg(node, i))
	{
		if (is_valid_identifier(get_node_arg(node, i)))
			env_remove(env, get_node_arg(node, i));
		else
		{
			ft_printf_fd(STDERR_FILENO,
				"minishell: unset: `%s': not a valid identifier\n",
				get_node_arg(node, i));
			ret = 1;
		}
		i++;
	}
	return (ret);
}
