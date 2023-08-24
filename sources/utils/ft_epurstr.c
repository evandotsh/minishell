/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_epurstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 16:28:27 by evmorvan          #+#    #+#             */
/*   Updated: 2023/08/22 16:28:27 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    notabu(char *str)
{
        int     i;

        i = 0;
        while (str[i] != '\0')
        {
                if (str[i] == '\t')
                        str[i] = ' ';
                i++;
        }
}

char    *decal_word(char *buff, int nb_decal, int pos)
{
        while (buff[pos + nb_decal] != '\0')
        {
                buff[pos] = buff[pos + nb_decal];
                pos++;
        }
        buff[pos] = '\0';
        return (buff);
}

char    *epur_str(char *str)
{
        int     i;

        notabu(str);
        i = 0;
        while (str[i] == ' ')
                i++;
        decal_word(str, i, 0);
        i = 0;
        while (str[i] != '\0')
        {
                if (str[i] == ' ')
                {
                        i++;
                        while (str[i] == ' ')
                                decal_word(str, 1, i);
                }
                i++;
        }
        i -= 1;
        while (str[i] == ' ')
                str[i--] = '\0';
        return (str);
}