/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:01:16 by jonchoi           #+#    #+#             */
/*   Updated: 2023/05/25 12:13:32 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envp.h"

char	**get_env_path(char **envp)
{
	char	**path;
	int		i;
	char	*env_path;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);
	env_path = envp[i] + 5;
	path = ft_split(env_path, ':');
	return (path);
}

void	init_envp_arr(t_env_info *info, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
		i++;
	info->envp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!info->envp)
		return ;
	i = 0;
	while (envp[i])
	{
		info->envp[i] = ft_strdup(envp[i]);
		i++;
	}
	info->envp[i] = NULL;
}

void	init_env(t_env_info *env_info, char **envp)
{
	char		*key;
	char		*value;
	int			i;
	t_env_node	*new;

	env_info->env_path = get_env_path(envp);
	init_envp_arr(env_info, envp);
	env_info->head = NULL;
	env_info->cnt = 0;
	i = 0;
	while (envp[i])
	{
		get_key_value(envp[i], &key, &value);
		new = new_env_node(key, value);
		add_env_node(&env_info->head, new, env_info);
		i++;
	}
}
