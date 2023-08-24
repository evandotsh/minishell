/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 08:57:45 by evmorvan          #+#    #+#             */
/*   Updated: 2023/04/17 17:35:33 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/**
	* Check if the given character is an alphanumeric character.
	* An alphanumeric character is any letter character or digit character.
	*
	* @param c The character to check.
	* @return Returns 1 if c is an alphanumeric character, otherwise returns 0.
*/
int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}
