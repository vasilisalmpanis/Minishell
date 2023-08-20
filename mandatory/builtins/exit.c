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

void	exit_builtin(t_env **lst, t_cmd *cmd)
{
	int	exit_code;

	if (cmd->args[0] == NULL)
	{
		exit_code = cmd->exit_code;
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		ft_env_free(lst);
		ft_cmd_lst_free_child(cmd);
		exit(exit_code);
	}
	if (cmd->args[1])
		ft_putstr_fd(" too many arguments\n", STDERR_FILENO);
	else
	{
		exit_code = ft_atoi(cmd->args[0]);
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		ft_env_free(lst);
		ft_cmd_lst_free_child(cmd);
		exit(exit_code);
	}
	return ;
}
