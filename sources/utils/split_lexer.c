/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:28:49 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/18 16:18:59 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_words(const char *str, char c)
{
	int	i;
	int	n;
	int	trigger;

	i = 0;
	n = 0;
	trigger = 0;
	while (str[n])
	{
		if (str[n] != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (str[n] == c)
			trigger = 0;
		n++;
	}
	return (i);
}

char	*word_dup(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	word = ft_strtrim_lexer(word);
	word = ft_epur_str(word);
	return (word);
}

int	verif_quote(const char *s, size_t i)
{
	if (s[i] == 39)
	{
		i++;
		while (s[i] != 39)
		{
			if (i > ft_strlen(s))
				return (ft_printf_fd(2, "minishell: Syntax Error\n"), 0);
			i++;
		}
	}
	else if (s[i] == 34)
	{
		i++;
		while (s[i] != 34)
		{
			if (i > ft_strlen(s))
				return (ft_printf_fd(2, "minishell: Syntax Error\n"), 0);
			i++;
		}
	}
	return (i);
}

char	**execute(char **split, char const *s, char c, int index)
{
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		if (s[i] == 39 || s[i] == 34)
		{
			i = verif_quote(s, i);
			if (i == 0)
				return (NULL);
		}
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			split[j++] = word_dup(s, index, i);
			index = -1;
		}
		i++;
	}
	split[j] = 0;
	return (split);
}

char	**ft_split_lexer(char const *s, char c)
{
	int		index;
	char	**split;

	if (!s)
		return (0);
	split = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!s || !split)
		return (NULL);
	index = -1;
	return (execute(split, s, c, index));
}
