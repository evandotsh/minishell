/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:27:55 by evmorvan          #+#    #+#             */
/*   Updated: 2023/04/17 17:35:33 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/**
	* Writes n zeroed bytes to the string s. If n is zero, bzero() does nothing.
	*
	* @param s The string to write to.
	* @param n The number of bytes to write.
*/
void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}
