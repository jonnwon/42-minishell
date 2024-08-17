/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 03:05:57 by jonchoi           #+#    #+#             */
/*   Updated: 2023/05/25 16:24:46 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_cmd_arr2(t_ast *node, char **arr, int cnt)
{
	t_ast	*cur;
	int		i;

	i = 0;
	cur = node;
	while (i < cnt)
	{
		arr[i] = cur->contents->data;
		cur = cur->left;
		i++;
	}
	arr[i] = NULL;
}

char	**set_cmd_arr(t_ast *node)
{
	int		cnt;
	char	**arr;
	t_ast	*cur;

	cur = node;
	if (!cur)
	{
		printf("No node in set_cmd_arr\n");
		return (NULL);
	}
	cnt = 0;
	while (cur)
	{
		cnt++;
		cur = cur->left;
	}
	arr = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (!arr)
	{
		printf("arr malloc error in set_cmd_arr\n");
		return (NULL);
	}
	set_cmd_arr2(node, arr, cnt);
	return (arr);
}
