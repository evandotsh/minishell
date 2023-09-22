/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:04:53 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/22 08:06:09 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	sh_print_export(t_env *env)
{
	while (env)
	{
		if (env->value[0] != '\0' && env->is_secret == 0)
			printf("declare -x %s=\"%s\"\n", env->key, env->value);
		else if (env->is_secret == 0)
			printf("declare -x %s\n", env->key);
		env = env->next;
	}
	return (0);
}

int	sh_add_export(char *key, char *value, t_env *env)
{
	int		ret;

	ret = 0;
	if (is_valid_identifier(key))
	{
		if (value)
			env_set(env, key, value);
		else
			env_set(env, key, "");
		if (ret != 1)
			ret = 0;
		free(key);
		free(value);
	}
	else
	{
		ret = 1;
		ft_printf_fd(STDERR_FILENO,
			"minishell: export: `%s': not a valid identifier\n", key);
	}
	return (ret);
}

int	sh_export(t_ast_node *node, t_env *env)
{
	int		i;
	char	**split;
	char	*key;
	char	*value;
	int		iter_ret;
	int		ret;

	i = 0;
	iter_ret = 0;
	ret = 0;
	if (!get_node_arg(node, 0))
		return (sh_print_export(env));
	else
	{
		while (get_node_arg(node, i))
		{
			split = ft_split(get_node_arg(node, i), '=');
			key = ft_strdup(split[0]);
			value = ft_strdup(split[1]);
			iter_ret = sh_add_export(key, value, env);
			if (ret != 1)
				ret = iter_ret;
			free_split(split);
			i++;
		}
	}
	return (ret);
}
