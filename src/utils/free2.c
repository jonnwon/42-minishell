/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 20:13:07 by jonchoi           #+#    #+#             */
/*   Updated: 2023/05/25 18:29:40 by jonchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_arr_2d(char ***arr)
{
	int	i;

	i = 0;
	while ((*arr)[i])
	{
		free((*arr)[i]);
		(*arr)[i] = NULL;
		i++;
	}
	free(*arr);
	*arr = NULL;
}

void	free_token(t_token **token)
{
	if (*token == NULL)
		return ;
	free((*token)->data);
	free(*token);
	*token = NULL;
}

void	free_token_lst(t_token **node)
{
	t_token	*cur;
	t_token	*next;

	cur = *node;
	while (cur)
	{
		next = cur->next;
		free(cur->data);
		free(cur);
		cur = next;
	}
	*node = NULL;
}
