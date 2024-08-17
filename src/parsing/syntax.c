/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 15:39:42 by jonchoi           #+#    #+#             */
/*   Updated: 2023/05/25 13:50:23 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_syntax_error(t_token *head)
{
	t_token	*cur;

	cur = head;
	while (cur)
	{
		if (cur->type == 1 && (ft_strlen(cur->data) > 1))
		{
			printf("minishell: syntax error near unexpected token '||'\n");
			return (1);
		}
		if (cur->next && cur->type == 1 && cur->next->type == 1)
		{
			printf("minishell: syntax error near unexpected token '||'\n");
			return (1);
		}
		cur = cur->next;
	}
	return (0);
}

static int	has_pipe_syntax_error(t_token *head)
{
	t_token	*cur;

	cur = head;
	if (cur)
	{
		while (cur->next)
			cur = cur->next;
		if (cur->type == 1)
		{
			printf("pipe syntax err\n");
			return (1);
		}
	}
	return (0);
}

int	pipe_err(t_token **head)
{
	if (has_syntax_error(*head))
		return (1);
	if (has_pipe_syntax_error(*head))
		return (1);
	return (0);
}

int	redir_err(t_token **head)
{
	t_token	*cur;

	cur = *head;
	while (cur)
	{
		if ((cur->type == 4 || cur->type == 6) && (ft_strlen(cur->data) > 2))
		{
			printf("Error: many redir err\n");
			return (1);
		}
		cur = cur->next;
	}
	cur = *head;
	while (cur)
	{
		if ((cur->type == 3 || cur->type == 4 || cur->type == 5 || \
		cur->type == 6) && (cur->next == NULL || cur->next->type != 0))
		{
			printf("bash: syntax error\n");
			return (1);
		}
		cur = cur->next;
	}
	return (0);
}
