/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 19:42:44 by jonchoi           #+#    #+#             */
/*   Updated: 2023/05/26 13:42:48 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_key_name2(char *key)
{
	int	i;

	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (1);
	i = 1;
	while (key[i])
	{
		if (!ft_isalpha(key[i]) && key[i] != '_' && !ft_isdigit(key[i]))
			return (1);
		i++;
	}
	return (0);
}

void	del_node_tmp_free(t_env_node *tmp)
{
	free(tmp->key);
	free(tmp->value);
	free(tmp);
}

void	delete_node_by_key(char *key, t_env_node *node, t_env_info *info)
{
	t_env_node	*tmp;
	t_env_node	*cur;

	(void)key;
	tmp = node;
	if (tmp == info->head)
	{
		info->head = tmp->next;
		del_node_tmp_free(tmp);
	}
	else
	{
		cur = info->head;
		while (cur)
		{
			if (cur->next == tmp)
			{
				cur->next = tmp->next;
				break ;
			}
			cur = cur->next;
		}
		del_node_tmp_free(tmp);
	}
	info->cnt--;
}

int	find_key_in_list(char *find_key, t_env_info *info)
{
	t_env_node	*cur;

	cur = info->head;
	while (cur)
	{
		if (!ft_strncmp(cur->key, find_key, ft_strlen(cur->key)))
		{
			delete_node_by_key(find_key, cur, info);
			return (0);
		}
		cur = cur->next;
	}
	return (1);
}

int	ft_unset(char **arr, t_env_info *info)
{
	int	i;
	int	j;

	i = 0;
	while (arr[i])
		i++;
	if (i > 1)
	{
		j = 1;
		while (j < i)
		{
			if (check_key_name2(arr[j]))
				printf("minishell: unset: '%s': \
				not a valid identifier\n", arr[j]);
			find_key_in_list(arr[j], info);
			j++;
		}
	}
	envp_arr_update(info);
	return (0);
}
