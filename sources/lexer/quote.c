/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfernand <sfernand@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 23:41:07 by sfernand          #+#    #+#             */
/*   Updated: 2023/09/11 02:21:45 by sfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	quote(char *str, int i, int j, char *result)
{
	int	x;
	int	a;

	x = 0;
	a = 0;
	if (str[i] == 34 && (a != 1 || x == 1))
		x = 1 - x;
	else if (str[i] == 39 && (x != 1 || a == 1))
		a = 1 - a;
	if ((str[i] != 34 && str[i] != 39) || (a == 1 || x == 1))
		result[j++] = ' ';
	if (str[i] != ' ')
		result[j++] = str[i];
}
