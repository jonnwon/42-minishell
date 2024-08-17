/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 18:24:29 by jonchoi           #+#    #+#             */
/*   Updated: 2023/05/26 12:33:31 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_minishell;

char	*find_value_by_key(char *key, t_env_info *info)
{
	t_env_node	*cur;
	char		*path;
	char		*code;

	if (!ft_strncmp(key, "?", ft_strlen(key)))
	{
		code = ft_itoa(g_minishell.status_code);
		return (code);
	}
	path = NULL;
	cur = info->head;
	while (cur)
	{
		if (!ft_strncmp(key, cur->key, ft_strlen(key)) && \
			!ft_strncmp(key, cur->key, ft_strlen(cur->key)))
			path = cur->value;
		cur = cur->next;
	}
	return (path);
}

void	change_type0(char *data, char **all_data)
{
	char	**arr;
	char	*tmp;
	char	*tmp2;
	int		i;

	arr = ft_split(data, '$');
	if (arr)
	{
		change_to_env_type10(arr);
		tmp = ft_substr(*all_data, 0, data - *all_data);
		i = 0;
		while (arr[i])
		{
			tmp2 = ft_strjoin(tmp, arr[i]);
			free(tmp);
			tmp = tmp2;
			i++;
		}
		free(*all_data);
		*all_data = tmp2;
		free_arr_2d(&arr);
	}
}

static void	expander_2(t_token **head, char *data, char *line)
{
	t_token	*cur;

	cur = *head;
	while (cur)
	{
		data = cur->data;
		if (cur->type == 10 && ft_strchr(data, '$'))
		{
			line = change_type10(data);
			if (line)
			{
				free(cur->data);
				cur->data = line;
				continue ;
			}
		}
		while (*data && cur->type == 0)
		{
			if (*data == '$' && *(data + 1))
				change_type0(data, &cur->data);
			data++;
		}
		cur = cur->next;
	}
}

void	expander(t_token **head)
{
	char	*data;
	char	*line;

	data = NULL;
	line = NULL;
	expander_2(head, data, line);
}
