/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfernand <sfernand@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 23:41:07 by sfernand          #+#    #+#             */
/*   Updated: 2023/09/05 23:10:32 by sfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	quote(char *str, int i, int j, char *result)
{
	int	x;
	int	a;

	x = 0;
	a = 0;
	if (str[i] == 34)
	{
		if (a != 1)
		{
			if (x == 1)
			{
				result[j++] = str[i++];
				x = 0;
			}
			else
				x = 1;
			result[j++] = ' ';
		}
	}
	else if (str[i] == 39)
	{
		if (x != 1)
		{
			if (a == 1)
			{
				result[j++] = str[i++];
				a = 0;
			}
			else
				a = 1;
			result[j++] = ' ';
		}
	}
}
