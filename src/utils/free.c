/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 20:13:07 by jonchoi           #+#    #+#             */
/*   Updated: 2023/05/25 13:44:55 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_ast(t_ast **node)
{
	if (*node == NULL)
		return ;
	free_ast(&(*node)->left);
	free_ast(&(*node)->right);
	free_token(&(*node)->contents);
	free(*node);
	*node = NULL;
}

void	free_token_arr(int **token_arr)
{
	if (*token_arr != NULL)
	{
		free(*token_arr);
		*token_arr = NULL;
	}
}

void	free_pid_list(pid_t **pid_list)
{
	if (*pid_list != NULL)
	{
		free(*pid_list);
		*pid_list = NULL;
	}
}

void	free_env_node(t_env_node **node)
{
	t_env_node	*cur;
	t_env_node	*next;

	cur = *node;
	while (cur)
	{
		next = cur->next;
		free(cur->key);
		free(cur->value);
		free(cur);
		cur = next;
	}
	*node = NULL;
}
