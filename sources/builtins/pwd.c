/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:21:33 by evmorvan          #+#    #+#             */
/*   Updated: 2023/08/24 12:33:09 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int sh_pwd(void)
{
    char	pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	printf("%s\n", pwd);
    return (0);
}