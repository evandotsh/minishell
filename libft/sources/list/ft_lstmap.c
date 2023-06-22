/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:59:58 by evmorvan          #+#    #+#             */
/*   Updated: 2023/04/17 17:35:27 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/**
	* Create a new list by applying the function f to each element of the given
	* list.
	* 
	* @param lst The pointer to the head of the original list.
	* @param f The function to apply to each element of the original list.
	* @param d The function used to delete the content of an element if
	* allocation fails.
	* @return A pointer to the head of the newly created list if successful, or
	* NULL if memory allocation fails.
*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*d)(void *))
{
	t_list	*new_lst;
	t_list	*new_lst_head;

	if (!lst || !f)
		return (NULL);
	new_lst = ft_lstnew(f(lst->content));
	if (!new_lst)
		return (NULL);
	new_lst_head = new_lst;
	while (lst->next)
	{
		lst = lst->next;
		new_lst->next = ft_lstnew(f(lst->content));
		if (!new_lst->next)
		{
			ft_lstclear(&new_lst_head, d);
			return (NULL);
		}
		new_lst = new_lst->next;
	}
	return (new_lst_head);
}
