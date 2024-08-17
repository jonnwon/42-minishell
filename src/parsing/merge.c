/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 16:09:56 by jonchoi           #+#    #+#             */
/*   Updated: 2023/05/26 12:39:48 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_merge_zero_type(t_token *cur, t_token *tmp)
{
	char	*line;

	cur->next = tmp->next;
	line = ft_strjoin(cur->data, tmp->data);
	free(cur->data);
	free(tmp->data);
	free(tmp);
	cur->data = line;
}

void	merge_zero_type(t_token **head)
{
	t_token	*cur;
	t_token	*tmp;

	cur = *head;
	while (cur && cur->next)
	{
		tmp = cur->next;
		if (cur->type == 0 && tmp->type == 0)
			process_merge_zero_type(cur, tmp);
		cur = cur->next;
	}
	cur = *head;
	while (cur && cur->next)
	{
		if (cur->type == 0 && cur->next->type == 0)
			merge_zero_type(head);
		cur = cur->next;
	}
}

static void	process_merge_tokens(t_token *cur)
{
	char	*str;
	char	*line;
	t_token	*tmp;

	str = ft_strjoin(cur->data, cur->next->data);
	line = ft_strjoin(str, cur->next->next->data);
	free(str);
	free(cur->data);
	free(cur->next->data);
	free(cur->next->next->data);
	cur->data = line;
	tmp = cur->next->next->next;
	free(cur->next->next);
	free(cur->next);
	cur->next = tmp;
}

void	merge_tokens(t_token **head)
{
	t_token	*cur;

	cur = *head;
	while (cur && cur->next && cur->next->next)
	{
		if ((cur->type == 10 && cur->next->type == 0 && \
			cur->next->next->type == 10) || \
			(cur->type == 9 && cur->next->type == 0 && \
			cur->next->next->type == 9))
			process_merge_tokens(cur);
		cur = cur->next;
	}
}
