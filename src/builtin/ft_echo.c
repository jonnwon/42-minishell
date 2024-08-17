/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:46:43 by jonchoi           #+#    #+#             */
/*   Updated: 2023/05/26 13:41:40 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_arg_echo(char **arr, int idx)
{
	int	tmp;

	tmp = idx;
	while (arr[idx])
	{
		if (idx > tmp && arr[idx -1])
			printf(" ");
		printf("%s", arr[idx]);
		idx++;
	}
	if (tmp == 1)
		printf("\n");
}

static int	is_option_echo(char *str)
{
	int	i;

	if (!str)
		return (0);
	if (str[0] != '-' || str[1] != 'n')
		return (0);
	i = 1;
	while (str[i] && str[i] == 'n')
		i++;
	if ((int)ft_strlen(str) == i)
		return (1);
	return (0);
}

int	ft_echo(char **arr)
{
	int	idx;

	idx = 1;
	while (is_option_echo(arr[idx]))
		idx++;
	print_arg_echo(arr, idx);
	return (0);
}
