/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:53:43 by evmorvan          #+#    #+#             */
/*   Updated: 2023/04/17 17:35:14 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/**
	* Takes as a parameter an element and frees the memory of the element’s
	* content using the function ’del’ given as a parameter and free the element.
	* The memory of ’next’ must not be freed.
	*
	* @param lst The element to free.
	* @param del The address of the function used to delete the content.
*/
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del || !lst->content)
		return ;
	del(lst->content);
	free(lst);
}
