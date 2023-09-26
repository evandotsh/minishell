/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 07:38:53 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/26 11:14:13 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*find_env(t_env *env, char *key)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

char	*expand_key(t_env *env, char *string, int *i)
{
	int		start;
	char	*key;
	t_env	*val;
	char	*tmp;

	start = *i;
	while (ft_isalnum(string[*i]) || string[*i] == '_' || string[*i] == '?')
		(*i)++;
	key = malloc((*i) - start + 1);
	tmp = ft_strdup(&string[start]);
	ft_strncpy(key, tmp, (*i) - start);
	key[(*i) - start] = '\0';
	val = find_env(env, key);
	free(key);
	if (val)
		return (val->value);
	else
		return ("");
}

char	*process_string(t_env *env, char *string, int *i)
{
	int		in_single_quotes;
	int		in_double_quotes;
	char	*val;

	in_single_quotes = 0;
	in_double_quotes = 0;
	while (string[*i] != '\0')
	{
		if (string[*i] == '\'')
			in_single_quotes = !in_single_quotes;
		else if (string[*i] == '\"')
			in_double_quotes = !in_double_quotes;
		if (string[*i] == '$' && (ft_isalpha(string[*i + 1])
				|| string[*i + 1] == '?')
			&& !in_single_quotes)
		{
			(*i)++;
			val = expand_key(env, string, i);
			return (val);
		}
		else
			return (NULL);
	}
	return (NULL);
}

char	*expand(t_env *env, char *string)
{
	char	*result;
	int		i;
	int		j;
	char	*processed_str;
	int		len;

	result = malloc(ft_strlen(string) + 1);
	i = 0;
	j = 0;
	while (string[i] != '\0')
	{
		processed_str = process_string(env, string, &i);
		if (processed_str != NULL)
		{
			len = ft_strlen(processed_str);
			result = ft_realloc(result, j, j + len + 1);
			ft_strcpy(&result[j], processed_str);
			j += len;
		}
		else
			result[j++] = string[i++];
	}
	result[j] = '\0';
	return (result);
}

void	expand_tokens(t_token *token, t_env *env)
{
	t_token	*tmp;
	char	*tmp_value;

	tmp = token;
	if (token == NULL)
		return ;
	while (tmp)
	{
		if (tmp->quote_type != '\'')
		{
			tmp_value = expand(env, tmp->token);
			free(tmp->token);
			tmp->token = tmp_value;
		}
		tmp = tmp->next;
	}
}
