/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:28:47 by evmorvan          #+#    #+#             */
/*   Updated: 2023/04/17 17:35:27 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/**
	* Allocates and returns a new string, which is the result of the
	* concatenation of ’s1’ and ’s2’.
	*
	* @param s1 The prefix string.
	* @param s2 The suffix string.
	* @return The new string. NULL if the allocation fails.
*/
char	*ft_strjoin(char const *s1, char const *s2)
{
	int		total_len;
	int		i;
	char	*joined;

	if (!s1 || !s2)
		return (NULL);
	total_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	joined = malloc(sizeof(char) * total_len);
	if (!joined)
		return (NULL);
	i = 0;
	while (*s1)
		joined[i++] = *s1++;
	while (*s2)
		joined[i++] = *s2++;
	joined[i] = '\0';
	return (joined);
}
