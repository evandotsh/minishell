/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:44:11 by evmorvan          #+#    #+#             */
/*   Updated: 2023/04/17 17:35:11 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/**
	* Add the given element to the beginning of the given list.
	*
	* @param lst The address of a pointer to the first link of a list.
	* @param new The address of a pointer to the element to be added to the list.
*/
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}
