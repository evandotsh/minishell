/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:04:53 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/05 14:14:21 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int sh_print_export(t_env *env)
{
    while (env)
    {
        if (env->value[0] != '\0')
            printf("declare -x %s=%s\n", env->key, env->value);
        else
            printf("declare -x %s\n", env->key);
        env = env->next;
    }
    return (0);
}

int sh_export(t_ast_node *node, t_env *env)
{
    int i;
    char *key;
    char *value;

    i = 0;
    printf("Executing builtin export\n");
    if (!get_node_arg(node, 0))
        return (sh_print_export(env));
    while (get_node_arg(node, i))
    {
        key = ft_split_lexer(get_node_arg(node, i), '=')[0];
        value = ft_split_lexer(get_node_arg(node, i), '=')[1];
        printf("Export %s=%s to env\n", key, value);
        if (value)
            env_set(env, key, value);
        else
            env_set(env, key, "");
        i++;
    }
    return (0);
}