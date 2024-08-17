/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:24:01 by geonwule          #+#    #+#             */
/*   Updated: 2023/05/26 13:41:21 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_key(char *key, t_env_info *info)
{
	t_env_node	*cur;

	cur = info->head;
	while (cur)
	{
		if (!ft_strncmp(key, cur->key, ft_strlen(cur->key)))
			return (1);
		cur = cur->next;
	}
	return (0);
}

void	set_value(char *key, char *value, t_env_info *info)
{
	t_env_node	*cur;

	cur = info->head;
	while (cur)
	{
		if (!ft_strncmp(key, cur->key, ft_strlen(cur->key)) && \
			!ft_strncmp(key, cur->key, ft_strlen(key)))
		{
			if (cur->value)
				free(cur->value);
			cur->value = value;
			return ;
		}
		cur = cur->next;
	}
}
