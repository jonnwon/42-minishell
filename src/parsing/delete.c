/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 15:57:20 by jonchoi           #+#    #+#             */
/*   Updated: 2023/05/26 12:38:28 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_del_double_quotes(t_token *cur)
{
	char	*data;
	int		len;

	while (cur->type == 10 && cur->data && (cur->data[0] == '\"' || \
				cur->data[ft_strlen(cur->data) - 1] == '\"'))
	{
		if (cur->data[0] == '\"')
		{
			len = ft_strlen(cur->data) - 1;
			data = ft_substr(cur->data, 1, len);
			free(cur->data);
			cur->data = data;
		}
		if (cur->data[ft_strlen(cur->data) - 1] == '\"')
		{
			len = ft_strlen(cur->data) - 1;
			data = ft_substr(cur->data, 0, len);
			free(cur->data);
			cur->data = data;
		}
	}
}

void	delete_double_quotes(t_token **head)
{
	t_token	*cur;

	cur = *head;
	while (cur)
	{
		process_del_double_quotes(cur);
		if (cur->type == 10)
			cur->type = 0;
		cur = cur->next;
	}
}

void	delete_single_quotes(t_token **head)
{
	t_token	*cur;
	char	*data;
	int		len;

	cur = *head;
	while (cur)
	{
		if (cur->type == 9)
		{
			len = ft_strlen(cur->data) - 2;
			data = ft_substr(cur->data, 1, len);
			free(cur->data);
			cur->data = data;
			cur->type = 0;
		}
		cur = cur->next;
	}
}

void	space_and_paren_del(t_token **head)
{
	t_token	*cur;
	t_token	*tmp;

	cur = *head;
	if (cur->type == 2)
	{
		*head = cur->next;
		free(cur->data);
		free(cur);
	}
	cur = *head;
	while (cur && cur->next)
	{
		tmp = cur->next;
		if (cur->next->type == 2 || cur->next->type == 7 || \
			cur->next->type == 8)
		{
			cur->next = cur->next->next;
			free(tmp->data);
			free(tmp);
		}
		cur = cur->next;
	}
}

void	delete_empty_data(t_token **head)
{
	t_token	*cur;
	t_token	*tmp;

	cur = *head;
	while (cur && cur->next)
	{
		tmp = cur->next;
		if (!ft_strncmp(tmp->data, "", ft_strlen(tmp->data)))
		{
			cur->next = cur->next->next;
			free(tmp->data);
			free(tmp);
		}
		cur = cur->next;
	}
}
