/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 18:00:53 by jonchoi           #+#    #+#             */
/*   Updated: 2023/05/26 13:41:05 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_dir(char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
		return (1);
	else
		return (0);
	return (0);
}

void	err_msg_cd(char *path, int dir_flag)
{
	if (dir_flag)
	{
		if (access(path, F_OK) != 0)
			printf("minishell: cd: %s: No such file or directory\n", path);
		else if (access(path, X_OK) != 0)
			printf("minishell: cd: %s: Permission denied\n", path);
		else
			printf("minishell: cd: %s: Undefoned error\n", path);
	}
	else
	{
		if (access(path, F_OK) != 0)
			printf("minishell: cd: %s: No such file or directory\n", path);
		else if (opendir(path) == NULL)
			printf("minishell: cd: %s: Not a directory\n", path);
		else if (access(path, X_OK) != 0)
			printf("minishell: cd: %s: Permission denied\n", path);
		else
			printf("minishell: cd: %s: Undefined error\n", path);
	}
}

void	mv_to_home_value(char *path, t_env_info *info)
{
	char	*home_value;

	(void)path;
	home_value = find_value_by_key("HOME", info);
	if (!home_value)
		printf("minishell: cd: $HOME not set\n");
	else if (chdir(home_value) != 0)
	{
		err_msg_cd(home_value, is_dir(home_value));
	}
}

void	upd_pwd(char *path, t_env_info *info)
{
	t_env_node	*new;
	char		*pwd_value;
	char		*pwd;

	(void)path;
	if (!find_key("OLDPWD", info))
	{
		printf("no find OLDPWD so make new_node\n");
		new = new_env_node("OLDPWD", "");
		add_env_node(&info->head, new, info);
	}
	if (find_key("PWD", info))
	{
		pwd_value = ft_strdup(find_value_by_key("PWD", info));
		set_value("OLDPWD", pwd_value, info);
		pwd = getcwd(NULL, 0);
		set_value("PWD", pwd, info);
	}
	else
		set_value("OLDPWD", "", info);
}

int	ft_cd(char **arr, t_env_info *info)
{
	char	*path;

	path = arr[1];
	if (!path)
		mv_to_home_value(path, info);
	else if (chdir(path) != 0)
	{
		err_msg_cd(path, is_dir(path));
		return (1);
	}
	else
		upd_pwd(path, info);
	envp_arr_update(info);
	return (0);
}
