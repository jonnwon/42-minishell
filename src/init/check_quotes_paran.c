/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes_paran.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:02:14 by jonchoi           #+#    #+#             */
/*   Updated: 2023/05/25 20:02:24 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_quotes(char *input, char s_or_d)
{
	int	in_quotes;
	int	i;

	in_quotes = 0;
	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == s_or_d)
			in_quotes = !in_quotes;
		i++;
	}
	if (!in_quotes)
		return (1);
	return (0);
}

static int	check_paren(char *input)
{
	int	cnt;
	int	i;

	cnt = 0;
	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '(')
			cnt++;
		else if (input[i] == ')')
			cnt--;
		if (cnt < 0)
			return (0);
		i++;
	}
	if (cnt == 0)
		return (1);
	return (0);
}

int	check_quotes_paren(char *input)
{
	if (!check_quotes(input, '\"'))
	{
		ft_putendl_fd("Error: Double are not closed.", STDOUT_FILENO);
		return (1);
	}
	if (!check_quotes(input, '\''))
	{
		ft_putendl_fd("Error: Single are not closed.", STDOUT_FILENO);
		return (1);
	}
	if (!check_paren(input))
	{
		ft_putendl_fd("Error: Parentheses are not closed.", STDOUT_FILENO);
		return (1);
	}
	return (0);
}
