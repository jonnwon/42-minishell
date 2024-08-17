/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 15:43:46 by jonchoi           #+#    #+#             */
/*   Updated: 2023/05/26 12:36:59 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_type(int *arr, int size, int idx, int *len)
{
	int	type;

	type = arr[idx];
	*len = 1;
	while (idx < size - 1)
	{
		if (arr[idx] != arr[idx + 1])
			return (type);
		idx++;
		(*len)++;
	}
	return (type);
}

t_token	*new_token_node(int type, char *data)
{
	t_token	*node;

	node = (t_token *)malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->type = type;
	node->data = data;
	node->next = NULL;
	return (node);
}

void	add_token_node(t_token **head, t_token *new)
{
	t_token	*cur;

	if (*head == NULL)
		*head = new;
	else
	{
		cur = *head;
		while (cur->next != NULL)
			cur = cur->next;
		cur->next = new;
	}
}

void	make_token_lst(int *arr, char *input, t_token **head)
{
	int		type;
	char	*data;
	int		idx;
	t_token	*new;
	int		len;

	idx = 0;
	len = 0;
	while ((size_t)idx < ft_strlen(input))
	{
		type = get_type(arr, ft_strlen(input), idx, &len);
		data = ft_substr(input, idx, len);
		new = new_token_node(type, data);
		add_token_node(head, new);
		idx += len;
	}
}
