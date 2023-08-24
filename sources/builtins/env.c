/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:24:36 by evmorvan          #+#    #+#             */
/*   Updated: 2023/08/24 12:34:27 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

int sh_env(t_env *env)
{
    while (env)
    {
        printf("%s=%s\n", env->key, env->value);
        env = env->next;
    }
    return (0);
}