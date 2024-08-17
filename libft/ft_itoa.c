/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 23:54:18 by jonchoi           #+#    #+#             */
/*   Updated: 2022/07/19 23:46:06 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*ft_cutnum(unsigned int num, size_t *size)
{
	char	*result;

	result = (char *)malloc(sizeof(char) * (*size + 1));
	if (!result)
		return (0);
	result[*size] = '\0';
	while (num)
	{
		result[*size - 1] = num % 10 + '0';
		num /= 10;
		(*size)--;
	}
	return (result);
}

static	size_t	*size_check(int n, size_t *size)
{
	while (n)
	{
		n /= 10;
		(*size)++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	size_t			size;
	char			*result;
	unsigned int	num;

	size = 0;
	num = 0;
	if (n > 0)
		num = n;
	else if (n <= 0)
	{
		num = -n;
		size += 1;
	}
	size = *size_check(n, &size);
	result = ft_cutnum(num, &size);
	if (num == 0)
		result[0] = '0';
	else if (size == 1 && result[1] != '\0')
		result[0] = '-';
	return (result);
}
