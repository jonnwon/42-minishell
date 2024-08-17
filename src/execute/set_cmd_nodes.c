/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_nodes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 03:01:44 by jonchoi           #+#    #+#             */
/*   Updated: 2023/05/25 16:26:18 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_cmd_cnt(t_ast *node)
{
	int		pipe_cnt;

	if (node->contents->type != 1)
		return (1);
	pipe_cnt = 0;
	while (node->contents->type == 1)
	{
		pipe_cnt++;
		node = node->left;
		if (!node->contents)
		{
			exit(1);
		}
	}
	return (pipe_cnt + 1);
}

void	preorder_cmd(t_ast *node, t_ast **cmd_nodes, int idx)
{
	if (node->contents->type == 0)
	{
		cmd_nodes[idx] = node;
		return ;
	}
	preorder_cmd(node->left, cmd_nodes, idx - 1);
	preorder_cmd(node->right, cmd_nodes, idx);
}

t_ast	**set_cmd_nodes(t_ast *root)
{
	t_ast	**cmd_nodes;
	int		cmd_cnt;

	cmd_cnt = set_cmd_cnt(root);
	cmd_nodes = (t_ast **)malloc(sizeof(cmd_nodes) * (cmd_cnt + 1));
	if (!cmd_nodes)
	{
		printf("cmd_nodes malloc err in set_cmd_nodes\n");
		return (NULL);
	}
	preorder_cmd(root, cmd_nodes, cmd_cnt - 1);
	cmd_nodes[cmd_cnt] = NULL;
	return (cmd_nodes);
}
