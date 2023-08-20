/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmpani <valmpani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 11:38:20 by valmpani          #+#    #+#             */
/*   Updated: 2023/08/20 11:38:20 by valmpani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strisnum(const char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	if (str[0] == '-'  || str[0] == '+')
		i++;
	if (ft_strlen(str + 1) > 18)
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	exit_builtin(t_env **lst, t_cmd *cmd)
{
	int	exit_code;

	if (!cmd)
		exit(0);
	if (cmd->args[0] == NULL)
	{
		exit_code = cmd->exit_code;
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		ft_env_free(lst);
		ft_cmd_lst_free_child(cmd);
		exit(exit_code);
	}
	if (cmd->args[1])
		return (ft_putstr_fd(" too many arguments\n", STDERR_FILENO), 1);
	else
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		if (cmd->args[0] && ft_strisnum(cmd->args[0]) == 0)
		{
			exit_code = 255;
			ft_putstr_fd(" numeric argument required\n", STDERR_FILENO);
		}
		else
			exit_code = ft_atoi(cmd->args[0]);
		ft_env_free(lst);
		ft_cmd_lst_free_child(cmd);
		exit(exit_code);
	}
	return (0);
}
