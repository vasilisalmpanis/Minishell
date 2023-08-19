/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_stdin_stdout.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:40:53 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/19 10:24:47 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_stdout(int *fd_in_out, int **fd, t_cmd *cmd)
{
	if (fd_in_out[OUT] != 0)
	{
		if (dup2(fd_in_out[OUT], STDOUT_FILENO) == -1)
			return (1);
		close(fd_in_out[OUT]);
	}
	if (fd_in_out[OUT] == 0)
	{
		if (cmd->next)
		{
			if (dup2(fd[cmd->cmd_id][1], STDOUT_FILENO) == -1)
				return (1);
		}
	}
	return (0);
}

int	set_stdin(int flag, int *fd_in_out, t_cmd *cmd, int **fd)
{
	int	fd_temp;

	if (flag == 0)
	{
		fd_temp = open("temp", O_RDONLY);
		if (fd_temp == -1)
			return (1);
		if (dup2(fd_temp, STDIN_FILENO) == -1)
			return (1);
		close(fd_temp);
		unlink(HEREDOC);
	}
	else if (flag == 1)
	{
		if (dup2(fd_in_out[IN], STDIN_FILENO) == -1)
			return (1);
		close(fd_in_out[IN]);
	}
	else if (flag == -1)
		if (cmd->cmd_id > 0)
			if (dup2(fd[cmd->cmd_id - 1][0], STDIN_FILENO) == -1)
				return (1);
	return (0);
}
