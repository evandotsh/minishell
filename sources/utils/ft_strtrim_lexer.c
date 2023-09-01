/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_lexer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfernand <sfernand@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 15:14:45 by sfernand          #+#    #+#             */
/*   Updated: 2023/09/01 15:56:28 by sfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_isspace(const char str)
{
    char    c;

    c = ' ';
    if (str == ' ' || str == '\t')
        return (1);
    else
        return (0);
}

char    *ft_strtrim_lexer(const char *str)
{
    char *result;
    size_t length = 0;
    const char *end;

    if (str == NULL)
        return NULL;
    while (ft_isspace(*str))
        str++;
    if (*str == '\0') 
    {
        result = (char *)malloc(1);
        if (result != NULL)
            result[0] = '\0';
        return result;
    }
    end = str + strlen(str) - 1;
    while (end > str && ft_isspace(*end))
        end--;
    length = end - str + 1;
    result = (char *)malloc(length + 1);
    if (result != NULL)
    {
        strncpy(result, str, length);
        result[length] = '\0';
    }
    return (result);
}