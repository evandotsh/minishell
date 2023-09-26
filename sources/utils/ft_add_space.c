/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 01:13:32 by sfernand          #+#    #+#             */
/*   Updated: 2023/09/26 16:54:09 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*check_str(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '>' || str[0] == '<' || str[0] == '|')
		return (NULL);
	while (str[i])
	{
		if (str[i] == '|' && (str[i + 2] == '>' || str[i + 2]))
			return (NULL);
		if (str[i] == '<' && str[i + 1] == '<'
			&& (str[i + 2] == '<' || str[i + 2] == '\0'))
			return (NULL);
		if (str[i] == '>' && str[i + 1] == '>'
			&& (str[i + 2] == '>' || str[i + 2] == '\0'))
			return (NULL);
		i++;
	}
	return (str);
}

char	*add_spaces(char *str)
{
	size_t	len;
	char	*result;
	size_t	i;
	size_t	j;

	len = ft_strlen(str);
	i = 0;
	j = 0;
	if (str == NULL || len == 0)
		return (free(str), NULL);
	result = (char *)malloc((len * 2 + 1) * sizeof(char));
	if (result == NULL)
	{
		free(str);
		return (NULL);
	}
	str = check_str(str);
	if (str == NULL)
	{
		free(str);
		return (free(result), NULL);
	}
	result = check_redir(str, i, j, result);
	free(str);
	return (result);
}
