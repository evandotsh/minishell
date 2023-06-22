/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 09:14:40 by evmorvan          #+#    #+#             */
/*   Updated: 2023/04/17 17:35:27 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/**
	* Locates the first occurrence of c (converted to a char) in the string
	* pointed to by s. The terminating null character is considered to be part
	* of the string; therefore if c is `\0', the functions locate the
	* terminating `\0'.
	*
	* @param str The string to be searched.
	* @param c The character to be located.
	* @return A pointer to the first occurrence of the character c in the string
	* str, or NULL if the character is not found.
*/
char	*ft_strchr(char const *str, int c)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (char) c)
			return ((char *)&str[i]);
		i++;
	}
	if ((char) c == '\0')
		return ((char *)&str[i]);
	return (NULL);
}
