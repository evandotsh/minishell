/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 08:56:43 by evmorvan          #+#    #+#             */
/*   Updated: 2023/04/17 17:35:33 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/**
	* Check if the given character is a digit character.
	* A digit character is any character within the 0-9 range.
	*
	* @param c The character to check.
	* @return Returns 1 if c is a digit character, otherwise returns 0.
*/
int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
