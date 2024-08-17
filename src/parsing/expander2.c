/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 18:24:29 by jonchoi           #+#    #+#             */
/*   Updated: 2023/05/26 12:35:00 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_minishell;

static void	ft_if(char *data, t_type10 *type10, int i, int *cnt)
{
	type10->tmp = ft_substr(data, 0, i);
	if (type10->value == NULL)
		type10->line = ft_strjoin(type10->tmp, "");
	else
		type10->line = ft_strjoin(type10->tmp, type10->value);
	free(type10->tmp);
	(*cnt)++;
}

static void	ft_else(t_type10 *type10, int j, int *k, int key_len)
{
	char	*data;

	data = type10->data;
	type10->tmp = ft_substr(type10->data, *k, j - key_len - 1 - *k);
	type10->tmp2 = ft_strjoin(type10->line, type10->tmp);
	if (type10->line)
		free(type10->line);
	free(type10->tmp);
	if (type10->value == NULL)
		type10->line = ft_strjoin(type10->tmp2, "");
	else
		type10->line = ft_strjoin(type10->tmp2, type10->value);
	free(type10->tmp2);
}

static void	change_type_10_3(t_type10 *type10, int *j, int *key_len)
{
	char	*key;
	char	*data;
	int		i;

	i = type10->i;
	data = type10->data;
	while (data[*j])
	{
		if (data[*j] == ' ' || data[*j] == '\"' || data[*j] == '$' \
			|| data[*j] == '\'')
			break ;
		(*j)++;
	}
	*key_len = *j - i - 1;
	key = ft_substr(type10->data, i + 1, *key_len);
	type10->value = find_value_by_key(key, &g_minishell.info);
	free(key);
}

static void	change_type10_2(t_type10 *type10, int *k)
{
	int		cnt;
	int		i;
	int		j;
	int		key_len;

	cnt = 0;
	i = 0;
	while (type10->data[i])
	{
		if (type10->data[i] == '$' && type10->data[i + 1] != ' ' \
			&& type10->data[i + 1] != '\"')
		{
			j = i + 1;
			type10->i = i;
			change_type_10_3(type10, &j, &key_len);
			if (cnt == 0)
				ft_if(type10->data, type10, i, &cnt);
			else
				ft_else(type10, j, k, key_len);
			*k = j;
		}
		i++;
	}
}

char	*change_type10(char *data)
{
	t_type10	type10;
	int			k;

	type10.data = data;
	type10.line = data;
	change_type10_2(&type10, &k);
	type10.tmp = ft_substr(data, k, ft_strlen(data) - k);
	type10.tmp2 = ft_strjoin(type10.line, type10.tmp);
	free(type10.tmp);
	free(type10.line);
	type10.line = type10.tmp2;
	return (type10.line);
}
