/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evmorvan <evmorvan@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 11:51:03 by evmorvan          #+#    #+#             */
/*   Updated: 2023/09/11 14:34:57 by evmorvan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/libft.h"

char	*pf_strnew(size_t size)
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
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*pf_uitoa(unsigned int n)
{
	char			*dst;
	unsigned int	count;
	unsigned int	i;
	unsigned int	num;

	num = n;
	count = count_size(num);
	i = 0;
	if (count == 0)
		count++;
	dst = pf_strnew(count);
	if (dst == NULL)
		return (NULL);
	while (count-- > i)
	{
		dst[count] = (num % 10) + '0';
		num /= 10;
	}
	return (dst);
}

int	pf_putuint_fd(unsigned int nb, int fd)
{
	char	*str;
	int		len;

	str = pf_uitoa(nb);
	len = pf_putstr_fd(str, fd);
	free(str);
	return (len);
}

int	pf_putnbr_fd(int nb, int fd)
{
	char	*str;
	int		len;

	str = ft_itoa(nb);
	len = pf_putstr_fd(str, fd);
	free(str);
	return (len);
}
