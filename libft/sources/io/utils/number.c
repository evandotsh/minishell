/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 11:51:03 by evmorvan          #+#    #+#             */
/*   Updated: 2023/04/09 15:23:11 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

char	*ft_strnew(size_t size)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (NULL);
	ft_bzero(str, size + 1);
	return (str);
}

unsigned int	count_size(unsigned int n)
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

char	*ft_uitoa(unsigned int n)
{
	char			*dst;
	unsigned int	count;
	unsigned int	i;
	unsigned int	num;

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

int	ft_putuint(unsigned int nb)
{
	char	*str;
	int		len;

	str = ft_uitoa(nb);
	len = ft_putstr(str);
	free(str);
	return (len);
}

int	ft_putnbr(int nb)
{
	char	*str;
	int		len;

	str = ft_itoa(nb);
	len = ft_putstr(str);
	free(str);
	return (len);
}
