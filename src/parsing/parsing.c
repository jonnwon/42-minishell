/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:09:25 by jonchoi           #+#    #+#             */
/*   Updated: 2023/05/25 19:56:01 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_minishell;

static int	check_only_space(t_token **head)
{
	t_token	*cur;

	cur = *head;
	while (cur)
	{
		if (cur->type != 2 && cur->type != 22)
			return (0);
		cur = cur->next;
	}
	return (1);
}

static int	process_token(t_token **head)
{
	merge_tokens(head);
	expander(head);
	delete_double_quotes(head);
	delete_single_quotes(head);
	merge_zero_type(head);
	if (check_only_space(head))
		return (1);
	space_and_paren_del(head);
	delete_empty_data(head);
	return (0);
}

static int	is_syntax_err(t_token **head)
{
	if (pipe_err(head) || redir_err(head))
	{
		g_minishell.status_code = 1;
		free_token_lst(head);
		return (1);
	}
	return (0);
}

static int	func(t_token **head)
{
	if (process_token(head))
	{
		free_token_lst(head);
		return (1);
	}
	space_and_paren_del(head);
	delete_empty_data(head);
	if (is_syntax_err(head))
	{
		free_token_lst(head);
		return (1);
	}
	return (0);
}

t_ast	*parsing(char *input)
{
	t_token	*head;
	t_ast	*ast;
	int		*token_arr;
	int		line_len;

	line_len = ft_strlen(input);
	token_arr = init_arr(input);
	set_arr(input, token_arr, ft_strlen(input));
	clear_quotes(token_arr, line_len);
	head = NULL;
	make_token_lst(token_arr, input, &head);
	free_token_arr(&token_arr);
	if (func(&head))
		return (NULL);
	ast = set_tree(head);
	if (!ast)
		free_token_lst(&head);
	return (ast);
}
