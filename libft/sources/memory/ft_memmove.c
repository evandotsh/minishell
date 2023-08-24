/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:25:20 by evmorvan          #+#    #+#             */
/*   Updated: 2023/04/17 17:35:27 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/**
	* Copies len bytes from string src to string dst. The two strings may
	* overlap; the copy is always done in a non-destructive manner.
	*
	* @param dst The destination string.
	* @param src The source string.
	* @param len The number of bytes to copy.
	* @return The destination string.
*/
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*dst_c;
	unsigned char	*src_c;

	if (dst == NULL && src == NULL)
		return (NULL);
	i = 0;
	dst_c = (unsigned char *)dst;
	src_c = (unsigned char *)src;
	if (src_c < dst_c)
	{
		while (len--)
			dst_c[len] = src_c[len];
	}
	else
	{
		while (i < len)
		{
			dst_c[i] = src_c[i];
			i++;
		}
	}
	return (dst);
}
