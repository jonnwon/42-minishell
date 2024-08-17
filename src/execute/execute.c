/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 03:05:57 by jonchoi           #+#    #+#             */
/*   Updated: 2023/05/25 16:24:32 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_minishell;

int	is_builtin(t_ast *node)
{
	const char	*builtin[] = \
		{"echo", "cd", "pwd", "export", "unset", "env", "exit"};
	int			i;

	if (node->contents->type != 0)
		return (0);
	i = 0;
	while (i < 7)
	{
		if (!ft_strncmp(node->contents->data, builtin[i] \
			, ft_strlen(builtin[i])))
			return (1);
		i++;
	}
	return (0);
}

int	builtin_exec(t_ast *node, char **cmd_arr)
{
	char	*cmd;

	cmd = node->contents->data;
	if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)))
		return (ft_echo(cmd_arr));
	else if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
		return (ft_cd(cmd_arr, &g_minishell.info));
	else if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
		return (ft_pwd());
	else if (!ft_strncmp(cmd, "env", ft_strlen(cmd)))
		return (ft_env(&g_minishell.info));
	else if (!ft_strncmp(cmd, "export", ft_strlen(cmd)))
		return (ft_export(cmd_arr, &g_minishell.info));
	else if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
		return (ft_unset(cmd_arr, &g_minishell.info));
	else if (!ft_strncmp(cmd, "exit", ft_strlen(cmd)))
		return (ft_exit(cmd_arr));
	return (1);
}

void	exec_parent(t_ast *node)
{
	char	**cmd_arr;
	t_ast	*cmd_node;

	cmd_node = node;
	cmd_arr = set_cmd_arr(node);
	if (set_heredoc(cmd_node))
		return ;
	if (set_redir(cmd_node))
		return ;
	g_minishell.status_code = builtin_exec(cmd_node, cmd_arr);
	cmd_node = NULL;
	free(cmd_arr);
	cmd_arr = NULL;
}

int	exec(t_ast *root)
{
	if (is_builtin(root))
		exec_parent(root);
	else
		exec_child(root);
	signal(SIGINT, handle_sigint);
	return (1);
}
