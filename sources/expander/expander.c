/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 07:38:53 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/07 07:42:33 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void expander(t_ast_node *node, t_env *env) {
    if (node == NULL) {
        return;
    }

    if (node->type == ND_CMD) {
        for (int i = 0; i < node->cmd_arg_count; i++) {
            char *arg = node->cmd_args[i]->arg_value;

            // Check if argument is enclosed in single quotes
            if (arg[0] == '\'') {
                continue;
            } else
			{
				printf("arg: %c\n", arg[0]);
			}

            t_env *curr_env = env;
            while (curr_env != NULL) {
                char *key = curr_env->key;
                char *key_with_dollar = malloc(strlen(key) + 2);
                strcpy(key_with_dollar, "$");
                strcat(key_with_dollar, key);

                // Loop until all instances of key_with_dollar are replaced in arg
                char *ptr;
                while ((ptr = strstr(arg, key_with_dollar)) != NULL) {
                   
                    char *new_arg = calloc(strlen(arg) + strlen(curr_env->value) + 1, sizeof(char));

                    strncpy(new_arg, arg, ptr - arg);
                    strcat(new_arg, curr_env->value);
                    strcat(new_arg, ptr + strlen(key_with_dollar));

                    //free(arg);
                    arg = new_arg;
                }

                //free(key_with_dollar);
                curr_env = curr_env->next;
            }
            
            // Update the argument value with the expanded value
            //free(node->cmd_args[i]->arg_value);
            node->cmd_args[i]->arg_value = arg;

        }
    } else if (node->type == ND_PIPE) {
        expander(node->pipe_lhs, env);
        expander(node->pipe_rhs, env);
    }
}