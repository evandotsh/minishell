/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:55:59 by evmorvan          #+#    #+#             */
/*   Updated: 2023/04/17 17:35:12 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/**
	* Delete and free the given element and every successor of that element,
	* using the function ’del’ and free(3).
	* Finally, the pointer to the list must be set to NULL.
	*
	* @param lst The address of a pointer to an element.
	* @param del The address of the function used to delete the content of the
	* element.
*/
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*cur;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		cur = *lst;
		*lst = (*lst)->next;
		ft_lstdelone(cur, del);
	}
}
