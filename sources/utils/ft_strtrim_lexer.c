/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_lexer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 15:14:45 by sfernand          #+#    #+#             */
/*   Updated: 2023/09/11 12:28:14 by evmorvan         ###   ########.fr       */
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

char	*ft_strncpy(char *dest, const char *src, size_t n)
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
	return (dest);
}

char	*ft_strtrim_lexer(const char *str)
{
	const char	*start;
	const char	*end;
	size_t		length;
	char		*result;

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
	return (result);
}
