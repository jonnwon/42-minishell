/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:13:41 by jonchoi           #+#    #+#             */
/*   Updated: 2023/05/26 13:47:53 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <termios.h>
# include "envp.h"
# include "builtin.h"
# include <fcntl.h>
# include <sys/ioctl.h>

# define PROMPT	"\033[0;31mminishell>\033[0m "

/* 명령, 인수, 연산자(파이프, 리다이렉션)를 개별 토큰으로, 연결리스트로 만든 것 */
typedef struct s_token
{
	int				type;
	char			*data;
	struct s_token	*next;
}					t_token;

/* 추상 구문 트리(ATS)노드 (구문(void *data)이 추상적이어서 추상 구조 트리) */
typedef struct s_ast
{
	t_token			*contents;
	struct s_ast	*left;
	struct s_ast	*right;
	struct s_ast	*parents;
}					t_ast;

typedef struct s_global
{
	t_env_info	info;
	int			status_code;
	int			is_heredoc;
	pid_t		pid;
	t_ast		*root;
}	t_global;

/* expander3 : change_type10*/
typedef struct s_type10
{
	char	*data;
	char	*tmp;
	char	*tmp2;
	char	*value;
	char	*line;
	int		i;
}	t_type10;

/*
type int

0: word
1: |
2: space
3: <
4: <<
5: >
6: >>
7: (
8: )
9: '
10:"
22:\t
*/

/* init */
void	init_terminal(void);
void	init_signal(void);
void	sig_handler(int sig);
void	handle_sigint_heredoc(int sig);

/* parsing */
void	init_setting(char **envp);
t_ast	*parsing(char *input);

/* check */
int		pipe_err(t_token **head);
int		redir_err(t_token **head);

/* quotes */
int		check_quotes_paren(char *input);

/* token */
void	make_token(t_token **head, int *token_arr, char *input, int line_len);
void	make_token_lst(int *arr, char *input, t_token **head);

/* merge */
void	merge_zero_type(t_token **head);
void	merge_tokens(t_token **head);

/* utils */
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strcmp2(char *s1, char *s2);
int		p_error(char *str);
void	err_msg(char *path, int dir_flag);
int		is_dir2(char *path);

/* print */
void	print_arr_i(int *arr, int size);
void	print_test_func(t_token **head);
void	print_lst_token(t_token *head);
void	print_ast(t_ast *node, int depth);
void	print_lst(t_env_node *head);
void	print_arr_2d(char **arr);
void	print_cmd_list(t_ast **cmd_list);
void	print_cmd_nodes(t_ast **cmd_nodes);
void	print_tree(t_ast *node);

/* exec */
int		exec_child(t_ast *root);
pid_t	child_process(t_ast *cmd, int *i_fd);
pid_t	last_child_process(t_ast *cmd, int i_fd);

/* child1 */
int		exec_child(t_ast *root);

/* child2 */
pid_t	last_child_process(t_ast *cmd, int i_fd);
pid_t	child_process(t_ast *cmd, int *i_fd);
pid_t	*make_pid_list(t_ast **cmd_nodes);

/* child3 */
void	set_and_execve_child(t_ast *cmd);
int		run_heredoc(t_ast *node);
int		is_heredoc(t_ast *node);
char	*make_tmp_filename(t_ast *node);
t_ast	**set_cmd_nodes(t_ast *root);

/* execute.c */
int		is_builtin(t_ast *node);
char	**set_cmd_arr(t_ast *node);
int		set_i_fd(t_ast *node);
int		set_o_fd(t_ast *node);
int		set_fd(t_ast *node);
int		set_heredoc(t_ast *node);
int		set_redir(t_ast *node);
int		builtin_exec(t_ast *node, char **cmd_arr);
void	exec_parent(t_ast *node);
int		exec(t_ast *root);

/* init.c */
void	handle_sigint(int sig);
void	init_terminal(void);

/* expander */
void	expander(t_token **head);
char	*change_type10(char *data);
void	change_to_env_type10(char **arr);
char	*find_value_by_key(char *key, t_env_info *info);

/*tree*/
t_ast	*set_tree(t_token *head);
int		new_empty_ast(t_ast **node);
t_ast	*new_ast(t_token *token);
void	set_child(t_ast *parents, t_ast *child, char opt);

/*delete*/
void	delete_double_quotes(t_token **head);
void	delete_single_quotes(t_token **head);
void	space_and_paren_del(t_token **head);
void	delete_empty_data(t_token **head);

/*set_arr.c*/
int		*init_arr(char *input);
void	set_arr(char *input, int *arr, int len);

/*clear_quotes.c*/
void	clear_quotes(int *token_arr, int len);

/*free.c*/
void	free_ast(t_ast **node);
void	free_token(t_token **token);
void	free_arr_2d(char ***arr);
void	free_token_arr(int **token_arr);
void	free_pid_list(pid_t **pid_list);
void	free_env_node(t_env_node **node);
void	free_token_lst(t_token **node);
t_token	*new_token_node(int type, char *data);

#endif
