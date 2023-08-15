/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:45:22 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/15 16:41:06 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_files(t_cmd *cmd)
{
	int	fd_temp;

	fd_temp = 0;
	if (cmd->out_flag)
		fd_temp = open(cmd->out_file, O_RDWR | O_CREAT | O_TRUNC, 00644);
	if (cmd->app_flag)
	{
		close(fd_temp);
		fd_temp = open(cmd->app_file, O_RDWR | O_CREAT | O_APPEND, 00644);
	}
	if (fd_temp == -1)
		exit(EXIT_FAILURE);
	return (fd_temp);
}

int	open_outfiles_builtin(t_cmd *cmd, int **fd)
{
	int	fd_temp;

	if (cmd->out_flag || cmd->app_flag)
	{
		fd_temp = open_files(cmd);
		if (cmd->next)
		{
			if (dup2(fd[cmd->cmd_id][1], STDOUT_FILENO) == -1)
				exit(EXIT_FAILURE);
		}
		else
		{
			if (dup2(fd_temp, STDOUT_FILENO) == -1)
				exit(EXIT_FAILURE);
		}
		close(fd_temp);
	}
	return (0);
}

int	open_infile(t_cmd *cmd, int **fd)
{
	int	fd_temp;

	fd_temp = 0;
	// if (cmd->hd_flag)
	// {
	// 	fd_temp = heredoc(cmd);
	// }
	if (cmd->in_flag)
	{
		fd_temp = open(cmd->in_file, O_RDONLY);
		if (fd_temp == -1)
			return (printf("Error infile\n"), 1); // add proper err msg
		if (dup2(fd_temp, STDIN_FILENO) == -1)
			return (1);
		close(fd_temp);
	}
	else
	{
		if (cmd->cmd_id > 0)
		{
			if (dup2(fd[cmd->cmd_id - 1][0], STDIN_FILENO) == -1)
				return (1);
		}
	}
	return (0);
}

// int	heredoc(t_cmd *cmd)
// {
// 	int		fd;
// 	char	*buf;

// 	fd = open("temp", O_CREAT | O_TRUNC, 00644);
// 	if (fd == -1)
// 		exit(EXIT_FAILURE);
// 	while (1)
// 	{
// 		write(0, "> ", 2);
// 		buf = get_next_line(0);
// 		if (!buf)
// 			exit(EXIT_FAILURE);
// 		rm_newline(&buf);
// 		write(fd, buf, ft_strlen(buf));
// 		if (ft_memcmp(cmd->delim, buf, ft_strlen(cmd->delim) + 1) == 0)
// 			break ;
// 		free(buf);
// 	}
// 	return (fd);
// }

int	open_outfile(t_cmd *cmd, int **fd)
{
	int	fd_temp;

	if (cmd->out_flag || cmd->app_flag)
	{
		fd_temp = open_files(cmd);
		if (fd_temp == -1)
			exit(EXIT_FAILURE);
		if (dup2(fd_temp, STDOUT_FILENO) == -1)
			return (1);
		close(fd_temp);
	}
	else
	{
		if (cmd->next)
		{
			if (dup2(fd[cmd->cmd_id][1], STDOUT_FILENO) == -1)
				return (1);
		}
	}
	return (0);
}
