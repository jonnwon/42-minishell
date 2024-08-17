/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:02:51 by jonchoi           #+#    #+#             */
/*   Updated: 2023/05/25 13:46:10 by geonwule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	p_error(char *str)
{
	ft_putendl_fd(str, STDOUT_FILENO);
	exit(1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*c1;
	unsigned char	*c2;

	c1 = (unsigned char *)s1;
	c2 = (unsigned char *)s2;
	while (*c1 && *c2 && *c1 == *c2)
	{
		c1++;
		c2++;
	}
	return (*(unsigned char *)c1 - *(unsigned char *)c2);
}

int	ft_strcmp2(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (s1[i] != '\0')
		return (s1[i]);
	if (s2[i] != '\0')
		return (-s2[i]);
	return (0);
}

int	is_dir2(char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
	{
		printf("%s is a directory\n", path);
		return (1);
	}
	else
	{
		printf("%s is not a directory\n", path);
		return (0);
	}
}

void	err_msg(char *path, int dir_flag)
{
	if (dir_flag)
	{
		if (access(path, F_OK) != 0)
			printf("minishell: %s: No such file or directory\n", path);
		else if (access(path, X_OK) != 0)
			printf("minishell: %s: Permission denied\n", path);
		else
			printf("minishell: %s: Undefined error\n", path);
	}
	else
	{
		if (access(path, F_OK) != 0)
			printf("minishell: %s: No such file or directory\n", path);
		else if (opendir(path) == NULL)
			printf("minishell: %s: Not a directory\n", path);
		else if (access(path, X_OK) != 0)
			printf("minishell: %s: Permission denied\n", path);
		else
			printf("minishell: %s: Undefined error\n", path);
	}
}
