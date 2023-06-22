/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:46:24 by evmorvan          #+#    #+#             */
/*   Updated: 2023/04/17 17:35:27 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	count_substrings(char const *str, char separator)
{
	int	substring_count;

	substring_count = 0;
	while (*str)
	{
		if (*str == separator)
			str++;
		else
		{
			substring_count++;
			while (*str != '\0' && *str != separator)
				str++;
		}
	}
	return (substring_count);
}

static void	extract_substrings(char **substrings, const char *str, char sep)
{
	int			i;
	int			substring_count;
	const char	*start;

	i = 0;
	while (*str)
	{
		while (*str && *str == sep)
			str++;
		start = str;
		substring_count = 0;
		while (*str && *str != sep)
		{
			str++;
			substring_count++;
		}
		if (*(str - 1) != sep)
			substrings[i++] = ft_substr(start, 0, substring_count);
	}
	substrings[i] = NULL;
}

/**
	* Splits the string s into an array of substrings delimited by c.
	*
	* @param s The string to be split.
	* @param c The delimiter character.
	* @return The array of substrings delimited by c in s, or NULL if memory
	* allocation fails.
	* @note The returned array and its elements must be freed using free() when
	*  no longer needed.
*/
char	**ft_split(char const *str, char separator)
{
	char	**substrings;
	int		substring_count;

	if (!str)
		return (NULL);
	substring_count = count_substrings(str, separator);
	substrings = (char **)malloc(sizeof(char *) * (substring_count + 1));
	if (!substrings)
		return (NULL);
	extract_substrings(substrings, str, separator);
	return (substrings);
}
