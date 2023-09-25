/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:04:53 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/25 13:49:25 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_length(t_env *env)
{
	int		list_length;
	t_env	*temp;

	list_length = 0;
	temp = env;
	while (temp != NULL)
	{
		list_length++;
		temp = temp->next;
	}
	return (list_length);
}

void	sort_env(t_env *env, int listLength)
{
	int		i;
	t_env	*start;

	i = 0;
	while (i < listLength)
	{
		start = env;
		bubble_sort_env(start, listLength - i);
		i++;
	}
}

// Main function
int	sh_print_export(t_env *env)
{
	int	list_length;

	if (!env)
		return (0);
	list_length = get_length(env);
	sort_env(env, list_length);
	while (env)
	{
		if (env->value[0] != '\0' && (env->is_secret == 0 && ft_strcmp(env->key,
					"_") != 0))
			printf("declare -x %s=\"%s\"\n", env->key, env->value);
		else if (env->is_secret == 0 && ft_strcmp(env->key, "_") != 0)
			printf("declare -x %s\n", env->key);
		env = env->next;
	}
	return (0);
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
	{
		if (ft_strchr(arg, '='))
			key = ft_substr(arg, 0, ft_strchr(arg, '=') - arg);
		else
			key = ft_strdup(arg);
		value = ft_strdup("");
	}
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
