/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 18:24:29 by jonchoi           #+#    #+#             */
/*   Updated: 2023/05/26 12:35:43 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_minishell;

static void	change_to_env_type10_2(char **arr, int i)
{
	char	*value;

	value = NULL;
	value = find_value_by_key(arr[i], &g_minishell.info);
	if (value)
	{
		free(arr[i]);
		arr[i] = ft_strdup(value);
	}
	else
	{
		free(arr[i]);
		arr[i] = ft_strdup("");
	}
}

void	change_to_env_type10(char **arr)
{
	int		i;
	char	*status;
	char	*tmp;

	i = 0;
	while (arr[i])
	{
		if (arr[i][0] == '?')
		{
			status = ft_itoa(g_minishell.status_code);
			tmp = ft_substr(arr[i], 1, ft_strlen(arr[i]) - 1);
			free(arr[i]);
			arr[i] = ft_strjoin(status, tmp);
			free(status);
			free(tmp);
			i++;
			continue ;
		}
		change_to_env_type10_2(arr, i);
		i++;
	}
}
