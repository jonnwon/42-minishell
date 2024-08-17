/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 21:49:30 by jonchoi           #+#    #+#             */
/*   Updated: 2022/07/12 02:13:14 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	letter;

	letter = (char)c;
	i = ft_strlen(s);
	if (letter == '\0')
		return ((char *)s + i);
	while (i >= 0)
	{
		if (s[i] == letter)
			return ((char *)s + i);
		i--;
	}
	return (0);
}
