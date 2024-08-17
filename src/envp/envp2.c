/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:01:16 by jonchoi           #+#    #+#             */
/*   Updated: 2023/05/26 13:43:02 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"

void	get_key_value(char *line, char **key, char **value)
{
	int		i;

	i = 0;
	while (line[i] != '=' && line[i])
		i++;
	*key = ft_substr(line, 0, i);
	if ((int)ft_strlen(line) == i)
	{
		*value = NULL;
		return ;
	}
	*value = ft_substr(line, i + 1, ft_strlen(line) - i - 1);
}

t_env_node	*new_env_node(char *key, char *value)
{
	t_env_node	*node;

	node = (t_env_node *)malloc(sizeof(t_env_node));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

void	add_env_node(t_env_node **head, t_env_node *new, t_env_info *info)
{
	t_env_node	*cur;

	if (*head == NULL)
		*head = new;
	else
	{
		cur = *head;
		while (cur->next != NULL)
			cur = cur->next;
		cur->next = new;
	}
	info->cnt++;
}
