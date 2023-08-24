/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:27:41 by evmorvan          #+#    #+#             */
/*   Updated: 2023/04/17 17:35:33 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/**
	* Allocates memory for an array of count elements of size bytes each and
	* returns a pointer to the allocated memory. The memory is set to zero.
	*
	* @param count The number of elements to allocate.
	* @param size The size of each element.
	* @return A pointer to the allocated memory.
*/
void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (size && SIZE_MAX / size < count)
		return (NULL);
	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}
