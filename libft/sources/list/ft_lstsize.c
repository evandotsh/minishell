/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:47:21 by evmorvan          #+#    #+#             */
/*   Updated: 2023/04/17 17:35:27 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/**
	* Counts the number of elements in a list.
	*
	* @param lst The beginning of the list.
	* @return The number of elements in a list.
*/
int	ft_lstsize(t_list *lst)
{
	int		len;
	t_list	*cur;

	len = 0;
	cur = lst;
	while (cur)
	{
		len++;
		cur = cur->next;
	}
	return (len);
}
