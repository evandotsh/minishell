/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 12:22:27 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/11 12:23:02 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*env_get(t_env *env, char *key)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key)) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	env_remove(t_env *env, char *key)
{
	t_env	*tmp;

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

char	**env_to_envp_format(t_env *env)
{
	char	**envp;
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	envp = malloc(sizeof(char *) * (i + 1));
	if (!envp)
		return (NULL);
	i = 0;
	tmp = env;
	while (tmp)
	{
		envp[i] = ft_strjoin(tmp->key, "=");
		envp[i] = ft_strjoin(envp[i], tmp->value);
		i++;
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}

char	*get_exec_path_from_env(char *program, t_env *env)
{
	char	*path;
	char	**paths;
	int		i;

	if (access(program, F_OK) == 0)
		return (program);
	path = env_get(env, "PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	i = 0;
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		paths[i] = ft_strjoin(paths[i], program);
		if (access(paths[i], F_OK) == 0)
			return (paths[i]);
		i++;
	}
	return (NULL);
}

int	is_valid_identifier(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	i++;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
