/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 15:10:49 by jonchoi           #+#    #+#             */
/*   Updated: 2023/05/25 13:36:13 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_minishell;

int	set_fd(t_ast *node)
{
	int	type;
	int	err;

	err = 0;
	type = node->contents->type;
	if (type == 3 || type == 4)
		err = set_i_fd(node);
	else if (type == 5 || type == 6)
		err = set_o_fd(node);
	if (err)
	{
		g_minishell.status_code = 1;
		return (1);
	}
	return (0);
}

int	set_redir(t_ast *node)
{
	t_ast	*cur;
	int		err;

	err = 0;
	cur = node->right;
	while (cur)
	{
		err = set_fd(cur);
		cur = cur->right;
	}
	if (err)
		return (1);
	return (0);
}
