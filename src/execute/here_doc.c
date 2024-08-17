/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 22:42:14 by jonchoi           #+#    #+#             */
/*   Updated: 2023/05/25 16:25:02 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_minishell;

char	*make_tmp_filename(t_ast *node)
{
	t_ast	*delim_node;
	char	*file_name;
	char	*delim;

	delim_node = node->left;
	delim = node->left->contents->data;
	file_name = ft_strjoin(".tmp_", delim);
	if (!file_name)
	{
		printf("file_name strjoin fail in make_tmp_filename\n");
		return (NULL);
	}
	return (file_name);
}

static void	run_heredoc2(t_ast *node, int fd, char *delim)
{
	char	*line;

	(void)node;
	while (1)
	{
		line = readline(">");
		if (!line)
		{
			free(line);
			break ;
		}
		if (!ft_strncmp(delim, line, ft_strlen(line)))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
}

int	run_heredoc(t_ast *node)
{
	char	*file_name;
	int		fd;
	char	*delim;

	file_name = make_tmp_filename(node);
	delim = node->left->contents->data;
	fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		printf("open error in run_heredoc\n");
	free(file_name);
	run_heredoc2(node, fd, delim);
	close(fd);
	return (0);
}

int	is_heredoc(t_ast *node)
{
	if (node->contents->type == 4)
		return (1);
	return (0);
}

int	set_heredoc(t_ast *node)
{
	t_ast	*cur;

	cur = node->right;
	while (cur)
	{
		if (is_heredoc(cur))
		{
			signal(SIGINT, handle_sigint_heredoc);
			run_heredoc(cur);
		}
		if (g_minishell.is_heredoc == 1)
		{
			g_minishell.is_heredoc = 0;
			return (1);
		}
		cur = cur->right;
	}
	return (0);
}
