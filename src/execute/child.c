/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:48:07 by jonchoi           #+#    #+#             */
/*   Updated: 2023/05/25 16:25:18 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_minishell;

void	handle_sigquit(int sig)
{
	(void)sig;
	ft_putendl_fd("Quit: 3", 1);
}

void	handle_sigint_child(int sig)
{
	(void)sig;
	ioctl(0, TIOCSTI, "asdasasd");
	printf("asdasd\n");
	write(STDOUT_FILENO, "\n", 1);
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	if (rl_on_new_line() == -1)
		exit(1);
	rl_replace_line("", 1);
	rl_redisplay();
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
}

static void	wait_process(pid_t *pid_list, int *status_code)
{
	int		i;
	int		status;

	i = 0;
	status = 0;
	while (pid_list[i])
	{
		waitpid(pid_list[i], &status, 0);
		if (status > 0 && status <= 255)
		{
			status = 128 + status;
			status *= 256;
		}
		i++;
	}
	*status_code = status / 256;
}

static void	exec_child2(t_ast **cmd_nodes, pid_t *pid_list)
{
	int	i;
	int	i_fd;

	i = 0;
	i_fd = STDIN_FILENO;
	while (cmd_nodes[i + 1])
	{
		pid_list[i] = child_process(cmd_nodes[i], &i_fd);
		i++;
	}
	pid_list[i] = last_child_process(cmd_nodes[i], i_fd);
	wait_process(pid_list, &g_minishell.status_code);
	free_pid_list(&pid_list);
	free(cmd_nodes);
	cmd_nodes = NULL;
}

int	exec_child(t_ast *root)
{
	t_ast	**cmd_nodes;
	int		i;
	pid_t	*pid_list;

	cmd_nodes = set_cmd_nodes(root);
	pid_list = make_pid_list(cmd_nodes);
	i = 0;
	while (cmd_nodes[i])
	{
		if (set_heredoc(cmd_nodes[i]))
			return (1);
		i++;
	}
	signal(SIGINT, SIG_IGN);
	exec_child2(cmd_nodes, pid_list);
	return (0);
}
