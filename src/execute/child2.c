/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:48:07 by jonchoi           #+#    #+#             */
/*   Updated: 2023/05/25 13:01:50 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_minishell;

pid_t	last_child_process(t_ast *cmd, int i_fd)
{
	pid_t	pid;

	pid = fork();
	g_minishell.pid = pid;
	if (pid == -1)
		return (0);
	if (pid == 0)
	{
		dup2(i_fd, STDIN_FILENO);
		set_and_execve_child(cmd);
	}
	close(i_fd);
	return (pid);
}

static void	child_process2(pid_t pid, int *fd, int child_i_fd, t_ast *cmd)
{
	if (pid == 0)
	{
		close(fd[0]);
		dup2(child_i_fd, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		set_and_execve_child(cmd);
	}
}

pid_t	child_process(t_ast *cmd, int *i_fd)
{
	int		fd[2];
	pid_t	pid;
	int		child_i_fd;

	if (pipe(fd) == -1)
	{
		printf("pipe func err in child_process func\n");
		return (0);
	}
	child_i_fd = *i_fd;
	*i_fd = fd[0];
	pid = fork();
	if (pid == -1)
	{
		printf("child_process fork err in child_process func\n");
		return (0);
	}
	child_process2(pid, fd, child_i_fd, cmd);
	close(child_i_fd);
	close(fd[1]);
	return (pid);
}

pid_t	*make_pid_list(t_ast **cmd_nodes)
{
	pid_t	*pid_list;
	int		i;

	i = 0;
	while (cmd_nodes[i])
		i++;
	pid_list = (pid_t *)ft_calloc(i + 1, sizeof(pid_t));
	return (pid_list);
}
