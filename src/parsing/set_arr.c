/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_arr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:01:15 by jonchoi           #+#    #+#             */
/*   Updated: 2023/05/26 12:39:02 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*init_arr(char *input)
{
	int	*arr;
	int	i;

	arr = (int *)malloc(sizeof(int) * ft_strlen(input));
	if (!arr)
		return (NULL);
	i = 0;
	while ((size_t)i < ft_strlen(input))
	{
		arr[i] = 0;
		i++;
	}
	return (arr);
}

static void	set_arr_special_chars(char *input, int *arr, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (input[i] == '|')
			arr[i] = 1;
		else if (input[i] == ' ')
			arr[i] = 2;
		else if (input[i] == '<' && input[i + 1] == '<')
		{
			arr[i++] = 4;
			arr[i] = 4;
		}
		else if (input[i] == '<')
			arr[i] = 3;
		else if (input[i] == '>' && input[i + 1] == '>')
		{
			arr[i++] = 6;
			arr[i] = 6;
		}
		else if (input[i] == '>')
			arr[i] = 5;
		i++;
	}
}

static void	set_arr_other_chars(char *input, int *arr, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (input[i] == '(')
			arr[i] = 7;
		else if (input[i] == ')')
			arr[i] = 8;
		else if (input[i] == '\'')
			arr[i] = 9;
		else if (input[i] == '\"')
			arr[i] = 10;
		else if (input[i] == '\t')
			arr[i] = 22;
		i++;
	}
}

void	set_arr(char *input, int *arr, int len)
{
	set_arr_special_chars(input, arr, len);
	set_arr_other_chars(input, arr, len);
}
