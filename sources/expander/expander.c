/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 07:38:53 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/11 13:34:19 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	expander(t_ast_node *node, t_env *env)
{
	t_env	*curr_env;
	char	*arg;
	char	*key;
	char	*key_with_dollar;
	char	*ptr;
	char	*new_arg;
	int		i;

	if (node == NULL)
	{
		return ;
	}
	if (node->type == ND_CMD)
	{
		i = 0;
		while (i < node->cmd_arg_count)
		{
			arg = node->cmd_args[i]->arg_value;
			if (arg[0] == '\"' && arg[strlen(arg) - 1] == '\"')
			{
				memmove(arg, arg + 1, strlen(arg) - 2);
				arg[strlen(arg) - 2] = '\0';
			}
			if (arg[0] == '\'' && arg[strlen(arg) - 1] == '\'')
			{
				memmove(arg, arg + 1, strlen(arg) - 2);
				arg[strlen(arg) - 2] = '\0';
				i++;
				continue ;
			}
			curr_env = env;
			while (curr_env != NULL)
			{
				key = curr_env->key;
				key_with_dollar = malloc(strlen(key) + 2);
				strcpy(key_with_dollar, "$");
				strcat(key_with_dollar, key);
				ptr = strstr(arg, key_with_dollar);
				if (ptr != NULL)
				{
					new_arg = calloc(strlen(arg) + strlen(curr_env->value) + 1,
							sizeof(char));
					strncpy(new_arg, arg, ptr - arg);
					strcat(new_arg, curr_env->value);
					strcat(new_arg, ptr + strlen(key_with_dollar));
					free(arg);
					arg = new_arg;
				}
				free(key_with_dollar);
				curr_env = curr_env->next;
			}
			node->cmd_args[i]->arg_value = arg;
			i++;
		}
	}
	else if (node->type == ND_PIPE)
	{
		expander(node->pipe_lhs, env);
		expander(node->pipe_rhs, env);
	}
}
