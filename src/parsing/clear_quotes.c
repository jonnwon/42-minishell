/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:14:18 by jonchoi           #+#    #+#             */
/*   Updated: 2023/05/25 15:16:43 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clear_double_quotes(int *token_arr, int len)
{
	int	i;
	int	d_quote;

	i = 0;
	d_quote = 0;
	while (i < len)
	{
		if (token_arr[i] == 10)
		{
			d_quote = !d_quote;
			if (d_quote == 1 && token_arr[i + 1] != 10)
				token_arr[i + 1] = 0;
		}
		else if (d_quote)
			token_arr[i] = 0;
		i++;
	}
}

static void	clear_single_quotes(int *token_arr, int len)
{
	int	i;
	int	s_quote;

	i = 0;
	s_quote = 0;
	while (i < len)
	{
		if (token_arr[i] == 9)
		{
			s_quote = !s_quote;
			if (s_quote == 1 && token_arr[i + 1] != 9)
				token_arr[i + 1] = 0;
		}
		else if (s_quote)
			token_arr[i] = 0;
		i++;
	}
}

void	clear_quotes(int *token_arr, int len)
{
	clear_double_quotes(token_arr, len);
	clear_single_quotes(token_arr, len);
}
