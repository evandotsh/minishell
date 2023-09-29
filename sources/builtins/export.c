/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:04:53 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/29 13:23:29 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	sh_print_export(t_env *env)
{
	while (env)
	{
		if (env->value && env->is_secret != 1 && ft_strcmp(env->key,
				"_") != 0)
			printf("declare -x %s=\"%s\"\n", env->key, env->value);
		else if (env->is_secret != 1 && ft_strcmp(env->key, "_") != 0)
			printf("declare -x %s\n", env->key);
		env = env->next;
	}
	return (0);
}

void	handle_no_value(char *arg, char **key, char **value)
{
	if (ft_strchr(arg, '='))
	{
		*key = ft_substr(arg, 0, ft_strchr(arg, '=') - arg);
		*value = ft_strdup("");
	}
	else
	{
		*key = ft_strdup(arg);
		*value = NULL;
	}
}

int	sh_add_export(char *arg, t_env *env)
{
	char	*key;
	char	*value;
	int		ret;

	ret = 0;
	if (ft_strchr(arg, '=') && ft_strlen(ft_strchr(arg, '=')) > 1)
	{
		key = ft_substr(arg, 0, ft_strchr(arg, '=') - arg);
		value = ft_substr(arg, ft_strchr(arg, '=') - arg + 1,
				ft_strlen(ft_strchr(arg, '=')) - 1);
	}
	else
		handle_no_value(arg, &key, &value);
	if (!is_valid_identifier(key))
		ret = 1;
	if (ret == 0)
		env_set(env, key, value);
	multi_free(2, key, value);
	return (0);
}

int	sh_export(t_ast_node *node, t_env *env)
{
	int		i;
	int		ret;
	char	*tmp;

	i = 0;
	ret = 0;
	if (!get_node_arg(node, 0))
		return (sh_print_export(env));
	else
	{
		while (get_node_arg(node, i))
		{
			ret = sh_add_export(get_node_arg(node, i), env);
			if (ret == 1)
				ft_printf_fd(STDERR_FILENO,
					"minishell: export: `%s': not a valid identifier\n",
					get_node_arg(node, i));
			i++;
		}
	}
	tmp = ft_itoa(ret);
	env_set(env, "?", tmp);
	free(tmp);
	return (ret);
}
