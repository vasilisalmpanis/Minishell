/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:59:05 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/17 15:35:32 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	wait_for_children(t_cmd *start)
{
	int		status;
	int		exit_code;

	status = 0;
	exit_code = 0;
	while (start && start->next)
	{
		waitpid(start->pid, NULL, 0);
		start = start->next;
	}
	if (waitpid(start->pid, &status, 0) == -1)
		return (1);
	if (WIFEXITED(status))
	{
		exit_code = WEXITSTATUS(status);
		if (exit_code != 0)
			return (exit_code);
	}
	return (0);
}

int	exec_builtin(t_cmd *cmd, t_env *env_lst)
{
	int	exit_code;

	exit_code = 0;
	if (!ft_strncmp(cmd->cmd, "echo", ft_strlen(cmd->cmd)))
		exit_code = echo(cmd);
	else if (!ft_strncmp(cmd->cmd, "pwd", ft_strlen(cmd->cmd)))
		exit_code = pwd();
	else if (!ft_strncmp(cmd->cmd, "env", ft_strlen(cmd->cmd)))
		exit_code = env(env_lst, cmd);
	else if (!ft_strncmp(cmd->cmd, "cd", ft_strlen(cmd->cmd)))
		exit_code = cd_dir(cmd, env_lst);
	else if (!ft_strncmp(cmd->cmd, "export", ft_strlen(cmd->cmd)))
		exit_code = export(&env_lst, cmd);
	else if (!ft_strncmp(cmd->cmd, "unset", ft_strlen(cmd->cmd)))
		exit_code = unset(&env_lst, cmd);
	return (exit_code);
}
