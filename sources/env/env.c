/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 07:08:35 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/21 07:08:53 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*env_from_parent(char **envp)
{
	t_env	*env;
	t_env	*tmp;
	int		i;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		tmp = malloc(sizeof(t_env));
		if (!tmp)
			return (NULL);
		tmp->key = ft_strndup(envp[i], ft_strchr(envp[i], '=') - envp[i]);
		tmp->value = ft_strdup(ft_strchr(envp[i], '=') + 1);
		tmp->next = env;
		tmp->prev = NULL;
		if (env)
			env->prev = tmp;
		env = tmp;
		i++;
	}
	return (env);
}

void	env_add(t_env *env, char *env_var)
{
	char	*key;
	char	*value;

	key = ft_strndup(env_var, ft_strchr(env_var, '=') - env_var);
	value = ft_strdup(ft_strchr(env_var, '=') + 1);
	env_add_back(env, key, value);
}

void	env_set_secret(t_env *env, char *key)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key)) == 0)
		{
			tmp->is_secret = 1;
			return ;
		}
		tmp = tmp->next;
	}
}

void	env_set(t_env *env, char *key, char *value)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key)) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
	env_add_back(env, key, value);
}

void	env_add_back(t_env *env, char *key, char *value)
{
	t_env	*tmp;

	tmp = env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = malloc(sizeof(t_env));
	if (!tmp->next)
		return ;
	tmp->next->key = ft_strdup(key);
	tmp->next->value = ft_strdup(value);
	tmp->next->is_secret = 0;
	tmp->next->next = NULL;
	tmp->next->prev = tmp;
}
