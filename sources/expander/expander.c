/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 15:57:39 by evmorvan          #+#    #+#             */
/*   Updated: 2023/06/28 18:06:19 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*expand_env(char *arg, int j)
{
	char	*key;
	char	*value;
	char	*tmp;
	char	*tmp2;

	key = ft_substr(arg, j + 1, ft_strlen(arg) - j);
	value = getenv(key);
	if (value == NULL)
		value = "";
	tmp = ft_substr(arg, 0, j);
	tmp2 = ft_strjoin(tmp, value);
	free(tmp);
	tmp = ft_substr(arg, j + ft_strlen(key) + 1, ft_strlen(arg) - j);
	tmp2 = ft_strjoin(tmp2, tmp);
	free(tmp);
	free(arg);
	free(key);
	return (tmp2);
}

void	expander(t_cmd *cmd_list)
{
	t_cmd	*cmd;
	int		i;
	int		j;

	cmd = cmd_list;
	while (cmd != NULL)
	{
		i = 0;
		while (cmd->args[i] != NULL)
		{
			j = 0;
			while (cmd->args[i][j] != '\0')
			{
				if (cmd->args[i][j] == '$')
					cmd->args[i] = expand_env(cmd->args[i], j);
				j++;
			}
			i++;
		}
		cmd = cmd->next;
	}
}
