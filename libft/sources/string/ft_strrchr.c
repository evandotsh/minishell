/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 09:14:40 by evmorvan          #+#    #+#             */
/*   Updated: 2023/04/17 17:35:27 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/**
	* Locates the last occurrence of c (converted to a char) in the string
	* pointed to by s. The terminating null character is considered to be part
	* of the string; therefore if c is `\0', the functions locate the
	* terminating `\0'.
	*
	* @param str The string to be searched.
	* @param c The character to be located.
	* @return A pointer to the last occurrence of the character c in the string
	* str, or NULL if the character is not found.
*/
char	*ft_strrchr(char const *str, int c)
{
	int		i;

	i = ft_strlen(str);
	while (i != -1)
	{
		if (str[i] == (char) c)
			return ((char *) &str[i]);
		i--;
	}
	return (NULL);
}
