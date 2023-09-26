/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:00:27 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/25 21:37:12 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	bubble_sort_env(t_env *start, int listLength)
{
	int		j;
	t_env	temp_node;

	j = 0;
	while (j < listLength - 1)
	{
		if (ft_strcmp(start->key, start->next->key) > 0)
		{
			temp_node.key = start->key;
			temp_node.value = start->value;
			temp_node.is_secret = start->is_secret;
			start->key = start->next->key;
			start->value = start->next->value;
			start->is_secret = start->next->is_secret;
			start->next->key = temp_node.key;
			start->next->value = temp_node.value;
			start->next->is_secret = temp_node.is_secret;
		}
		start = start->next;
		j++;
	}
}

void	multi_free(int count, ...)
{
	va_list	ap;
	void	*ptr;

	va_start(ap, count);
	while (count--)
	{
		ptr = va_arg(ap, void *);
		free(ptr);
	}
	va_end(ap);
}

void	free_all_env(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		temp = env;
		env = env->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

void	postrun_exit(t_env *env, t_ast_node *node, int count, ...)
{
	va_list	ap;
	void	*ptr;

	va_start(ap, count);
	while (count--)
	{
		ptr = va_arg(ap, void *);
		free(ptr);
	}
	va_end(ap);
	free_all_env(env);
	free_all_nodes(node);
	exit(0);
}

char	*ft_strcat(char *dest, const char *src)
{
	size_t	dest_len;
	size_t	i;

	dest_len = ft_strlen(dest);
	i = 0;
	while (src[i])
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest);
}
