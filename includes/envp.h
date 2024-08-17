/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:00:21 by jonchoi           #+#    #+#             */
/*   Updated: 2023/05/26 13:38:33 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVP_H
# define ENVP_H

# include	"libft.h"
# include	<stdio.h>

typedef struct s_env_node
{
	char				*key;
	char				*value;
	struct s_env_node	*next;
}						t_env_node;

typedef struct s_env_info
{
	struct s_env_node	*head;
	char				**env_path;
	char				**envp;
	int					cnt;
}						t_env_info;

/*envp*/
void		init_env(t_env_info *env_info, char **envp);
char		**get_env_path(char **envp);
void		init_envp_arr(t_env_info *info, char **envp);
void		get_key_value(char *line, char **key, char **value);
t_env_node	*new_env_node(char *key, char *value);
void		add_env_node(t_env_node **head, t_env_node *new, t_env_info *info);

/*envp_arr_upadte*/
void		envp_arr_update(t_env_info *info);

#endif
