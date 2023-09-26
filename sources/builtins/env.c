/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 12:24:36 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/26 07:48:05 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	sh_env(t_env *env)
{
	t_env	*cursor;

	cursor = env;
	while (cursor)
	{
		if (cursor->value[0] != '\0' && cursor->is_secret != 1
			&& ft_strcmp(cursor->key, "_") != 0)
			printf("%s=%s\n", cursor->key, cursor->value);
		cursor = cursor->next;
	}
	env_set(env, "?", "0");
	return (0);
}
