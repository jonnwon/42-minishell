/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 02:37:37 by jonchoi           #+#    #+#             */
/*   Updated: 2023/05/25 18:07:07 by jonchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	make_ast_pipe(t_ast **cur, t_token *token)
{
	t_ast	*pipe;

	pipe = new_ast(token);
	if (!pipe)
		return (1);
	while ((*cur)->parents)
		*cur = (*cur)->parents;
	set_child(pipe, *cur, 'l');
	*cur = pipe;
	return (0);
}

static int	make_ast_redir(t_ast *cur, t_token **token)
{
	t_ast	*redir;
	t_ast	*file;

	redir = new_ast(*token);
	if (!redir)
		return (1);
	*token = (*token)->next;
	file = new_ast(*token);
	if (!file)
		return (1);
	if (!(*token)->next && !cur->contents)
		cur->contents = new_token_node(0, ft_strdup("true"));
	while (cur->right)
	{
		cur = cur->right;
	}
	set_child(cur, redir, 'r');
	set_child(redir, file, 'l');
	return (0);
}

static int	make_ast_word(t_ast	*cur, t_token *token)
{
	t_ast	*word;

	if (cur->contents == NULL)
	{
		cur->contents = token;
		return (0);
	}
	word = new_ast(token);
	if (!word)
		return (1);
	while (cur->left)
		cur = cur->left;
	set_child(cur, word, 'l');
	return (0);
}

static int	make_ast(t_ast	**cur, t_token **token)
{
	if (!(*cur))
		new_empty_ast(cur);
	else if ((*cur)->contents != NULL && (*cur)->contents->type == 1)
		new_empty_ast(cur);
	if ((*token)->type == 3 || (*token)->type == 4 || \
		(*token)->type == 5 || (*token)->type == 6)
		make_ast_redir(*cur, token);
	else
		make_ast_word(*cur, *token);
	return (0);
}

t_ast	*set_tree(t_token *head)
{
	t_ast	*cur;
	t_token	*token;

	cur = NULL;
	token = head;
	if (!token)
		return (NULL);
	while (token)
	{
		if (token->type == 1)
		{
			if (cur->contents == NULL)
				cur->contents = new_token_node(0, ft_strdup("true"));
			make_ast_pipe(&cur, token);
		}
		else
			make_ast(&cur, &token);
		token = token->next;
	}
	while (cur->parents)
		cur = cur->parents;
	return (cur);
}
