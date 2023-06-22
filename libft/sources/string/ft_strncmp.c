/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 11:39:03 by evmorvan          #+#    #+#             */
/*   Updated: 2023/04/17 17:35:27 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/**
	* Lexicographically compares the null-terminated strings s1 and s2.
	*
	* @param s1 The first string to compare.
	* @param s2 The second string to compare.
	* @param n The maximum number of bytes to compare.
	* @return An integer greater than, equal to, or less than 0, according as the
	* string s1 is greater than, equal to, or less than the string s2. The
	* comparison is done using unsigned characters, so that `\200' is greater
	* than `\0'.
*/
int	ft_strncmp(char const *s1, char const *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	n--;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n)
		i++;
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}
