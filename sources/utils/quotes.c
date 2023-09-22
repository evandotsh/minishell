/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:58:16 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/22 07:44:55 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	inter_quotes_loop(char *str, int *i, int *in_single_quotes,
			int *in_double_quotes)
{
	if (*in_single_quotes)
	{
		if (str[*i] == '\'')
			*in_single_quotes = 0;
		else
			return (1);
	}
	else if (*in_double_quotes)
	{
		if (str[*i] == '"')
			*in_double_quotes = 0;
		else
			return (1);
	}
	else
	{
		if (str[*i] == '\'')
			*in_single_quotes = 1;
		else if (str[*i] == '"')
			*in_double_quotes = 1;
		else
			return (1);
	}
	return (0);
}

char	*interpret_quotes(char *str)
{
	char	*result;
	char	*ptr;
	int		in_single_quotes;
	int		in_double_quotes;
	int		i;

	result = malloc(strlen(str) + 1);
	ptr = result;
	in_single_quotes = 0;
	in_double_quotes = 0;
	i = 0;
	while (str[i])
	{
		if (inter_quotes_loop(str, &i, &in_single_quotes, &in_double_quotes))
			*ptr++ = str[i];
		i++;
	}
	*ptr = '\0';
	return (result);
}

void	interpret_quotes_tokens(t_token *token)
{
	t_token	*tmp;
	char	*tmp_value;

	tmp = token;
	if (token == NULL)
		return ;
	while (tmp)
	{
		tmp_value = interpret_quotes(tmp->token);
		free(tmp->token);
		tmp->token = tmp_value;
		tmp = tmp->next;
	}
}
