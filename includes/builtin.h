/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonchoi <jonchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:31:06 by jonchoi           #+#    #+#             */
/*   Updated: 2023/05/26 13:38:41 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"
# include "envp.h"
# include <dirent.h>
# include <sys/stat.h>

int		ft_echo(char **arr);
int		ft_pwd(void);
int		ft_env(t_env_info *info);

/*ft_export.c*/
int		ft_export(char **arr, t_env_info *info);
int		check_key_name(char *key);

/*ft_unset.c*/
int		ft_unset(char **arr, t_env_info *info);
int		find_key_in_list(char *find_key, t_env_info *info);

/*ft_cd.c*/
int		ft_cd(char **arr, t_env_info *info);
char	*find_value_by_key(char *key, t_env_info *info);
int		find_key(char *key, t_env_info *info);
void	set_value(char *key, char *value, t_env_info *info);

/*ft_exit.c*/
int		ft_exit(char **cmd_arr);

#endif
