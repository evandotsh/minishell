/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 00:13:23 by evmorvan          #+#    #+#             */
/*   Updated: 2023/10/02 00:30:59 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_command_not_found(char **args, char *tmp)
{
	ft_printf_fd(STDERR_FILENO, "minishell: %s: command not found\n",
		args[0]);
	free_split(args);
	free(tmp);
	exit(127);
}

void	handle_path_is_directory(char **args, char *path)
{
	ft_printf_fd(STDERR_FILENO, "minishell: %s: is a directory\n",
		args[0]);
	free_split(args);
	free(path);
	exit(126);
}
