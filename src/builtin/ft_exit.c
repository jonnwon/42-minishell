/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwule <geonwule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 19:24:13 by geonwule          #+#    #+#             */
/*   Updated: 2023/05/26 13:42:23 by jonchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_minishell;

static int	sub_atoi(const char *str, int i, int *num, int sign)
{
	int	numeric;
	int	ret;

	numeric = 0;
	ret = 0;
	while (str[i] >= '0' && str[i] <= '9' && ++numeric)
	{
		*num = (*num * 10) + (str[i] - '0');
		if (sign == -1 || *num > 255)
			ret = -2;
		i++;
	}
	while (str[i] != '\0' || numeric == 0)
	{
		if (!ft_isdigit(str[i++]) || numeric == 1)
		{
			ret = -1;
			break ;
		}
	}
	return (ret);
}

static int	ft_atoi_2(const char *str)
{
	int	num;
	int	sign;
	int	i;
	int	error;

	num = 0;
	sign = 1;
	i = 0;
	while (str [i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str [i] == '-' || str [i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	error = sub_atoi(str, i, &num, sign);
	if (error)
		return (error);
	return (sign * num);
}

static int	exit_code_divide(char **cmd_arr, int exit_code, int cmd_arr_len)
{
	if (exit_code == -1)
	{
		printf("minishell: exit: %s: numeric argument required\n", cmd_arr[1]);
		exit(255);
	}
	if (cmd_arr_len > 2)
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}	
	if (exit_code == -2)
	{
		printf("exit_code_error\n");
		exit(1);
	}
	exit(exit_code);
	return (0);
}

int	ft_exit(char **cmd_arr)
{
	int	exit_code;
	int	cmd_arr_len;

	if (g_minishell.pid)
		printf("exit\n");
	cmd_arr_len = 0;
	while (cmd_arr[cmd_arr_len] != NULL)
		cmd_arr_len++;
	if (cmd_arr_len == 1)
		exit(0);
	exit_code = ft_atoi_2(cmd_arr[1]);
	return (exit_code_divide(cmd_arr, exit_code, cmd_arr_len));
}
