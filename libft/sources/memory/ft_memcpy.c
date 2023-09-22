/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 10:11:58 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/22 10:27:42 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/**
	* Copies n bytes from memory area src to memory area dst. If dst and src
	* overlap, behavior is undefined. Applications in which dst and src might
	* overlap should use memmove(3) instead.
	*
	* @param dst The destination memory area.
	* @param src The source memory area.
	* @param n The number of bytes to copy.
	* @return A pointer to the destination memory area.
*/
void	*ft_memcpy(void *dst, void const *src, size_t n)
{
	unsigned char	*dst_c;
	unsigned char	*src_c;

	if (!dst && !src)
		return (NULL);
	if (dst == src || n == 0)
		return (dst);
	dst_c = (unsigned char *)dst;
	src_c = (unsigned char *)src;
	while (n--)
		*dst_c++ = *src_c++;
	return (dst);
}
