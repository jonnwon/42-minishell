/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 15:51:55 by jonchoi           #+#    #+#             */
/*   Updated: 2023/05/25 13:42:33 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_child(t_ast *parents, t_ast *child, char opt)
{
	if (parents == NULL)
		return ;
	if (opt == 'l')
	{
		parents->left = child;
		if (child != NULL)
			child->parents = parents;
	}
	else if (opt == 'r')
	{
		parents->right = child;
		if (child != NULL)
			child->parents = parents;
	}
}

t_ast	*new_ast(t_token *token)
{
	t_ast	*new;

	new = (t_ast *)malloc(sizeof(t_ast));
	if (!new)
	{
		return (NULL);
	}
	new->contents = token;
	new->parents = NULL;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

int	new_empty_ast(t_ast **node)
{
	t_ast	*new;

	new = new_ast(NULL);
	if (!new)
	{
		return (1);
	}
	if (*node)
		set_child(*node, new, 'r');
	*node = new;
	return (0);
}
