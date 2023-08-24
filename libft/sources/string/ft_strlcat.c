/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:59:05 by evmorvan          #+#    #+#             */
/*   Updated: 2023/04/17 17:35:27 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/**
	* Appends string src to the end of dst. It will append at most
	* size - strlen(dst) - 1 characters. It will then NUL-terminate, unless size
	* is 0 or the original dst string was longer than size (in practice this
	* should not happen as it means that either size is incorrect or that dst is
	* not a proper string).
	*
	* @param dest The string to be appended upon.
	* @param src The NUL-terminated string to be appended.
	* @param size The size of the buffer pointed to by dest.
	* @return The total length of the string it tried to create.
*/
size_t	ft_strlcat(char *dest, char const *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;

	if ((!dest || !src) && size == 0)
		return (0);
	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	i = 0;
	if (size <= dest_len)
		return (src_len + size);
	while (i < size - dest_len - 1 && src[i])
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest_len + src_len);
}
