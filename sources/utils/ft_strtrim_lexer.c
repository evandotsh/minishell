/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_lexer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfernand <sfernand@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 15:14:45 by sfernand          #+#    #+#             */
/*   Updated: 2023/09/17 16:11:13 by sfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isspace(const char str)
{
	if (str == ' ' || str == '\t')
		return (1);
	else
		return (0);
}

char	*ft_strncpy(char *dest, char *src, size_t n)
{
	char		*d;
	const char	*s;
	size_t		i;

	d = dest;
	s = src;
	i = 0;
	while (i < n && *s != '\0')
	{
		*d++ = *s++;
		i++;
	}
	while (i < n)
	{
		*d++ = '\0';
		i++;
	}
	free(src);
	return (dest);
}

char	*ft_strtrim_lexer(char *str)
{
	char	*start;
	char	*end;
	size_t	length;
	char	*result;

	start = str;
	if (str == NULL)
		return (NULL);
	while (*start && ft_isspace(*start))
		start++;
	if (*start == '\0')
		return (ft_strdup(""), NULL);
	end = start + ft_strlen(start) - 1;
	while (end > start && ft_isspace(*end))
		end--;
	length = end - start + 1;
	result = (char *)malloc(length + 1);
	if (result != NULL)
	{
		ft_strncpy(result, start, length);
		result[length] = '\0';
	}
	else
		free(result);
	return (result);
}
