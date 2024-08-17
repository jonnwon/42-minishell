/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:02:14 by jonchoi           #+#    #+#             */
/*   Updated: 2023/05/26 12:56:51 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_minishell;

static void	normal_execute(char	*input)
{
	int		errno;
	int		fd[2];

	errno = 0;
	add_history(input);
	errno = check_quotes_paren(input);
	if (errno)
		return ;
	g_minishell.root = parsing(input);
	if (!g_minishell.root)
		return ;
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	if (exec(g_minishell.root))
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
	}
	if (g_minishell.root)
		free_ast(&g_minishell.root);
}

static void	main_loop(void)
{
	char	*input;

	while (1)
	{
		input = readline(PROMPT);
		if (!input)
		{
			ft_putendl_fd("\x1b[1A\033[11Cexit", STDOUT_FILENO);
			break ;
		}
		if (*input == '\0')
		{
			free(input);
			continue ;
		}
		else
			normal_execute(input);
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc != 1)
		p_error("Error: must not have arguments");
	init_env(&g_minishell.info, envp);
	init_terminal();
	init_signal();
	g_minishell.pid = 1;
	main_loop();
	free_arr_2d(&g_minishell.info.envp);
	free_arr_2d(&g_minishell.info.env_path);
	free_env_node(&g_minishell.info.head);
}
