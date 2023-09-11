/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:59:55 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/04 14:13:36 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_isnumber(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

int sh_exit(t_ast_node *node)
{
    int exit_code;

    printf("Executing builtin exit\n");
    if (get_node_arg_count(node) > 1)
    {
        printf("exit: too many arguments\n");
        exit_code = 255;
    }
    if (get_node_arg(node, 0))
    {
        if (ft_isnumber(get_node_arg(node, 0)))
            exit_code = ft_atoi(get_node_arg(node, 0));
        else
        {
            printf("exit: %s: numeric argument required\n", get_node_arg(node, 0));
            return (255);
        }
    }
    else
        exit_code = 0;
    printf("exitting with code %d\n", exit_code % 256);
    return (0);
}