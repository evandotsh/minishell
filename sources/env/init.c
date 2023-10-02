/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:32:21 by evmorvan          #+#    #+#             */
/*   Updated: 2023/10/02 12:32:56 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*initialize_env(char **envp)
{
	t_env	*env;
	t_env	*tmp;

	env = NULL;
	if (envp[0])
		env = env_from_parent(envp);
	else
	{
		tmp = malloc(sizeof(t_env));
		if (!tmp)
			return (NULL);
		tmp->key = ft_strdup("SHLVL");
		tmp->value = ft_strdup("1");
		tmp->is_secret = 0;
		tmp->next = env;
		tmp->prev = NULL;
		env = tmp;
	}
	env_set(env, "?", "0");
	env_set_secret(env, "?");
	return (env);
}
