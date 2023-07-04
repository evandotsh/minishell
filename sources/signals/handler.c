/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 12:14:08 by evmorvan          #+#    #+#             */
/*   Updated: 2023/06/29 12:15:17 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		printf("%s%s\n%s", C_PURPLE, make_prompt(), C_YELLOW);
	}
	else if (signum == SIGQUIT)
	{
		printf("\n");
		printf("%s%s\n%s", C_PURPLE, make_prompt(), C_YELLOW);
	}
}
