/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_arr_update.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 16:16:44 by jonchoi           #+#    #+#             */
/*   Updated: 2023/05/26 13:43:06 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	envp_arr_update_2(t_env_info *info, int i)
{
	int			j;
	char		*line;
	char		*tmp;
	t_env_node	*cur;

	j = 0;
	cur = info->head;
	while (j < i && cur)
	{
		if (cur->value)
		{
			line = ft_strdup(cur->key);
			tmp = ft_strjoin(line, "=");
			free(line);
			line = ft_strjoin(tmp, cur->value);
			free(tmp);
			tmp = NULL;
			info->envp[j] = line;
			j++;
		}
		cur = cur->next;
	}
	info->envp[j] = NULL;
}

void	envp_arr_update(t_env_info *info)
{
	int			i;
	t_env_node	*cur;

	free_arr_2d(&info->envp);
	i = 0;
	cur = info->head;
	while (cur)
	{
		if (cur->value != NULL)
			i++;
		cur = cur->next;
	}
	info->envp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!info->envp)
		return ;
	envp_arr_update_2(info, i);
}
