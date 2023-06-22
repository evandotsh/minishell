/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:00:08 by evmorvan          #+#    #+#             */
/*   Updated: 2023/04/17 17:35:27 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/**
	* Locates the first occurrence of the null-terminated string needle in the
	* string haystack, where not more than len characters are searched.
	* Characters that appear after a `\0' character are not searched.
	*
	* @param haystack The string to be searched.
	* @param needle The string to search for.
	* @param len The maximum number of characters to search.
	* @return A pointer to the first occurrence of needle in haystack, or NULL if
	* needle is not part of haystack.
*/
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if ((!haystack || !needle) && len == 0)
		return (NULL);
	if (!needle[i])
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		if (haystack[i] == needle[0])
		{
			j = 1;
			while (needle[j] && (i + j) < len && haystack[i + j] == needle[j])
				j++;
			if (!needle[j])
				return ((char *)haystack + i);
		}
		i++;
	}
	return (NULL);
}
