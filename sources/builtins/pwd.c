/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:21:33 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/25 09:14:53 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	sh_pwd(t_env *env)
{
	char	pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	printf("%s\n", pwd);
	env_set(env, "?", "0");
	return (0);
}
