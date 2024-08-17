/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:48:07 by jonchoi           #+#    #+#             */
/*   Updated: 2023/05/26 12:29:02 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_minishell;

static char	*check_cmd2(char **path, char *tmp, char *cmd)
{
	char	*abs_path;
	int		i;

	cmd = (void *)cmd;
	i = 0;
	while (path[i])
	{
		abs_path = ft_strjoin(path[i], tmp);
		if (!access(abs_path, X_OK))
		{
			free(tmp);
			return (abs_path);
		}
		i++;
		free(abs_path);
	}
	return (NULL);
}

static char	*check_cmd(char *cmd)
{
	char	*tmp;
	char	**path;
	char	*check_cmd2_ret;

	if (!access(cmd, X_OK) || cmd[0] == '/')
		return (cmd);
	tmp = ft_strjoin("/", cmd);
	path = get_env_path(g_minishell.info.envp);
	if (!path)
	{
		printf("minishell: %s: No such file or directory\n", cmd);
		exit(127);
	}
	check_cmd2_ret = check_cmd2(path, tmp, cmd);
	if (check_cmd2_ret)
		return (check_cmd2_ret);
	free(tmp);
	return (cmd);
}

static void	set_and_execve_child2(t_ast *cmd, char *cmd_path, char **cmd_arr)
{
	int		status_code;

	if ((!is_builtin(cmd) && access(cmd_path, X_OK)) \
		|| ft_strlen(cmd->contents->data) == 0)
	{
		if ((ft_strlen(cmd->contents->data) == 0))
			printf("minishell: : command not found\n");
		else
			printf("minishell: %s: command not found\n", cmd_path);
		exit(127);
	}
	if (is_builtin(cmd))
	{
		status_code = builtin_exec(cmd, cmd_arr);
		exit(status_code);
	}
}

void	set_and_execve_child(t_ast *cmd)
{
	char	**cmd_arr;
	char	*cmd_path;

	cmd_arr = set_cmd_arr(cmd);
	cmd_path = check_cmd(cmd->contents->data);
	if (set_redir(cmd))
		exit(1);
	set_and_execve_child2(cmd, cmd_path, cmd_arr);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_DFL);
	execve(cmd_path, cmd_arr, g_minishell.info.envp);
	exit(1);
}
