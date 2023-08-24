/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 07:08:35 by evmorvan          #+#    #+#             */
/*   Updated: 2023/08/24 12:45:43 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char    *ft_strndup(char *str, int n)
{
    char *new_str;

    new_str = malloc(sizeof(char) * (n + 1));
    if (!new_str)
        return (NULL);
    ft_strlcpy(new_str, str, n + 1);
    return (new_str);
}

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


void    env_add(t_env *env, char *env_var)
{
    char *key;
    char *value;

    key = ft_strndup(env_var, ft_strchr(env_var, '=') - env_var);
    value = ft_strdup(ft_strchr(env_var, '=') + 1);
    env_add_back(env, key, value);
}

void    env_set(t_env *env, char *key, char *value)
{
    t_env *tmp;

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

void    env_add_back(t_env *env, char *key, char *value)
{
    t_env *tmp;

    tmp = env;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = malloc(sizeof(t_env));
    if (!tmp->next)
        return ;
    tmp->next->key = ft_strdup(key);
    tmp->next->value = ft_strdup(value);
    tmp->next->next = NULL;
    tmp->next->prev = tmp;
}

char    *env_get(t_env *env, char *key)
{
    t_env *tmp;

    tmp = env;
    while (tmp)
    {
        if (ft_strncmp(tmp->key, key, ft_strlen(key)) == 0)
            return (tmp->value);
        tmp = tmp->next;
    }
    return (NULL);
}

void    env_remove(t_env *env, char *key)
{
    t_env *tmp;

    tmp = env;
    while (tmp)
    {
        if (ft_strncmp(tmp->key, key, ft_strlen(key)) == 0)
        {
            if (tmp->prev)
                tmp->prev->next = tmp->next;
            if (tmp->next)
                tmp->next->prev = tmp->prev;
            free(tmp->key);
            free(tmp->value);
            free(tmp);
            return ;
        }
        tmp = tmp->next;
    }
}
