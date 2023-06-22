/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 08:59:12 by evmorvan          #+#    #+#             */
/*   Updated: 2023/04/17 17:35:33 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/**
	* Check if the given character is an ASCII character.
	* An ASCII character is any character within the 0-127 range.
	*
	* @param c The character to check.
	* @return Returns 1 if c is an ASCII character, otherwise returns 0.
*/
int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}
