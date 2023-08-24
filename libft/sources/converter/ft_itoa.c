/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:40:06 by evmorvan          #+#    #+#             */
/*   Updated: 2023/04/17 17:35:33 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static char	*ft_strnew(size_t size)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (NULL);
	ft_bzero(str, size + 1);
	return (str);
}

static int	count_size(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		n *= -1;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

/**
	* Convert the given integer to a string.
	*
	* @param n The integer to convert.
	* @return Returns the converted string.
*/
char	*ft_itoa(int n)
{
	char		*dst;
	int			count;
	int			i;
	long int	num;

	num = n;
	count = count_size(num);
	i = 0;
	if (num < 0 || count == 0)
		count++;
	dst = ft_strnew(count);
	if (dst == NULL)
		return (NULL);
	if (num < 0)
	{
		num *= -1;
		dst[0] = '-';
		i++;
	}
	while (count-- > i)
	{
		dst[count] = (num % 10) + '0';
		num /= 10;
	}
	return (dst);
}
