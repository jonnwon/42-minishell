/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redir2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 15:10:49 by jonchoi           #+#    #+#             */
/*   Updated: 2023/05/26 12:32:13 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_i_fd_type_3(t_ast *node, int *err)
{
	char	*path;
	int		i_fd;

	path = node->left->contents->data;
	i_fd = open(path, O_RDONLY, 0644);
	if (i_fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		*err = 1;
	}
	return (i_fd);
}

static int	set_i_fd_type_4(t_ast *node, int *err)
{
	char	*path;
	int		i_fd;

	path = make_tmp_filename(node);
	i_fd = open(path, O_RDONLY, 0644);
	if (i_fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		*err = 1;
	}
	unlink(path);
	free(path);
	return (i_fd);
}

int	set_i_fd(t_ast *node)
{
	int		type;
	int		i_fd;
	int		err;

	err = 0;
	i_fd = 0;
	type = node->contents->type;
	if (type == 3)
		i_fd = set_i_fd_type_3(node, &err);
	else if (type == 4)
		i_fd = set_i_fd_type_4(node, &err);
	dup2(i_fd, STDIN_FILENO);
	close(i_fd);
	return (err);
}

static int	set_o_fd2(int type, char *path, int *err)
{
	int	o_fd;

	o_fd = 0;
	if (type == 5)
	{
		o_fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (o_fd == -1)
		{
			printf("o_fd open err in set_o_fd type5\n");
			*err = 1;
		}
	}
	else if (type == 6)
	{
		o_fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (o_fd == -1)
		{
			printf("o_fd open err in set_o_fd type6\n");
			*err = 1;
		}
	}
	return (o_fd);
}

int	set_o_fd(t_ast *node)
{
	int		type;
	int		o_fd;
	char	*path;
	int		err;

	err = 0;
	type = node->contents->type;
	path = node->left->contents->data;
	o_fd = set_o_fd2(type, path, &err);
	dup2(o_fd, STDOUT_FILENO);
	close(o_fd);
	return (err);
}
