/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 08:53:54 by evmorvan          #+#    #+#             */
/*   Updated: 2023/04/17 17:35:33 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/**
	* Check if the given character is an alphabetic character.
	* An alphabetic character is any letter character.
	*
	* @param c The character to check.
	* @return Returns 1 if c is an alphabetic character, otherwise returns 0.
*/
int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}
