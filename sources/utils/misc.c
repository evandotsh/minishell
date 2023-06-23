/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 12:00:32 by evmorvan          #+#    #+#             */
/*   Updated: 2023/06/23 14:43:35 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strndup(char *str, int n)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(char) * (n + 1));
	if (!new)
		return (NULL);
	while (i < n)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*get_pretty_cwd(void)
{
	char	*cwd;
	char	*home;
	char	*pretty_cwd;

	cwd = getcwd(NULL, 0);
	home = "/Users/evan";
	if (home && ft_strncmp(cwd, home, ft_strlen(home)) == 0)
	{
		pretty_cwd = ft_strjoin("~", cwd + ft_strlen(home));
		free(cwd);
		return (pretty_cwd);
	}
	return (cwd);
}
