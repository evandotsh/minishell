/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:17:10 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/11 14:09:28 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	sh_error(char *error, int ret)
{
	printf("minishell: %s\n", error);
	return (ret);
}

int	sh_cd(t_ast_node *node, t_env *env)
{
	char	*current_path;

	current_path = env_get(env, "PWD");
	if (get_node_arg_count(node) == 0)
	{
		if (chdir(env_get(env, "HOME")) == -1)
			return (sh_error("cd: HOME not set", 1));
	}
	else if (get_node_arg_count(node) >= 1)
	{
		if (ft_strncmp(get_node_arg(node, 0), "-", 2) == 0)
		{
			if (chdir(env_get(env, "OLDPWD")) == -1)
				return (sh_error("cd: OLDPWD not set", 1));
		}
		else if (ft_strncmp(get_node_arg(node, 0), "~", 2) == 0)
		{
			if (chdir(env_get(env, "HOME")) == -1)
				return (sh_error("cd: HOME not set", 1));
		}
		else
		{
			if (chdir(get_node_arg(node, 0)) == -1)
			{
				errno = ENOENT;
				perror("minishell");
				return (1);
			}
		}
	}
	env_set(env, "OLDPWD", current_path);
	env_set(env, "PWD", getcwd(NULL, 0));
	return (0);
}
