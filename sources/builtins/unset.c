/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:26:37 by evmorvan          #+#    #+#             */
/*   Updated: 2023/08/24 12:35:28 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

int sh_unset(t_ast_node *node, t_env *env)
{
    int i;

    i = 0;
    while (get_node_arg(node, i))
    {
        env_remove(env, get_node_arg(node, i));
        i++;
    }
    return (0);
}