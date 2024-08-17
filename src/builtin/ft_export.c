/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 18:55:41 by jonchoi           #+#    #+#             */
/*   Updated: 2023/05/25 17:44:15 by jonchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_minishell;

int	check_key_name(char *key)
{
	int	i;

	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (1);
	i = 1;
	while (key[i] && key[i] != '=')
	{
		if (!ft_isalpha(key[i]) && key[i] != '_' && !ft_isdigit(key[i]))
			return (1);
		i++;
	}
	return (0);
}

void	set_export(t_env_info *info, char *line)
{
	char		*key;
	char		*value;
	t_env_node	*new;

	get_key_value(line, &key, &value);
	if (find_key(key, &g_minishell.info))
	{
		free(key);
		set_value(key, value, &g_minishell.info);
		return ;
	}
	new = (t_env_node *)malloc(sizeof(t_env_node));
	if (!new)
	{
		printf("node malloc error in set_export\n");
		return ;
	}
	new->key = key;
	new->value = value;
	new->next = NULL;
	add_env_node(&info->head, new, info);
}

void	ft_export2(char **arr, t_env_info *info, int i)
{
	int	j;
	int	err_flag;

	j = 1;
	err_flag = 0;
	while (j < i && !err_flag)
	{
		if (check_key_name(arr[j]))
		{
			printf("check_key_name error\n");
			err_flag = 1;
		}
		j++;
	}
	j = 1;
	while (!err_flag && j < i)
	{
		set_export(info, arr[j]);
		j++;
	}
}

int	ft_export(char **arr, t_env_info *info)
{
	int	i;
	int	err_flag;

	i = 0;
	err_flag = 0;
	while (arr[i])
		i++;
	if (i > 0)
		ft_export2(arr, info, i);
	if (err_flag)
		return (1);
	envp_arr_update(info);
	return (0);
}
