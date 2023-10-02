/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 12:17:10 by evmorvan          #+#    #+#             */
/*   Updated: 2023/10/01 23:30:34 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	sh_error(t_env *env, char *error, int ret)
{
	ft_printf_fd(STDERR_FILENO, "minishell: %s\n", error);
	env_set(env, "?", "1");
	return (ret);
}

int	cd_to_home(t_env *env, char *current_path)
{
	if (chdir(env_get(env, "HOME")) == -1)
		return (sh_error(env, "cd: HOME not set", 1));
	env_set(env, "OLDPWD", current_path);
	env_set(env, "PWD", getcwd(NULL, 0));
	env_set(env, "?", "0");
	return (0);
}

int	cd_to_oldpwd(t_env *env, char *current_path)
{
	char	*oldpwd;

	oldpwd = env_get(env, "OLDPWD");
	if (!oldpwd)
		return (sh_error(env, "cd: OLDPWD not set", 1));
	if (chdir(oldpwd) == -1)
		return (sh_error(env, "cd: OLDPWD not set", 1));
	env_set(env, "OLDPWD", current_path);
	env_set(env, "PWD", getcwd(NULL, 0));
	env_set(env, "?", "0");
	return (0);
}

int	cd_to_directory(t_env *env, const char *directory, char *current_path)
{
	if (chdir(directory) == -1)
	{
		errno = ENOENT;
		perror("minishell");
		env_set(env, "?", "1");
		return (1);
	}
	env_set(env, "OLDPWD", current_path);
	env_set(env, "PWD", getcwd(NULL, 0));
	env_set(env, "?", "0");
	return (0);
}

int	sh_cd(t_ast_node *node, t_env *env)
{
	char	*current_path;

	current_path = env_get(env, "PWD");
	if (get_node_arg_count(node) == 0)
		return (cd_to_home(env, current_path));
	if (get_node_arg_count(node) >= 1)
	{
		if (ft_strcmp(get_node_arg(node, 0), "-") == 0)
			return (cd_to_oldpwd(env, current_path));
		else if (ft_strcmp(get_node_arg(node, 0), "~") == 0)
			return (cd_to_home(env, current_path));
		else
			return (cd_to_directory(env, get_node_arg(node, 0), current_path));
	}
	return (0);
}
