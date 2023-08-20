/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:45:22 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/19 10:24:13 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_files(t_cmd *cmd, int **fd)
{
	int	*fd_in_out;
	int	flag;

	flag = -1;
	signal(SIGINT, handle_sigint);
	if (open_heredocs(cmd->file, cmd->exit_code))
		return (1);
	fd_in_out = open_in_out_files(cmd->file);
	if (!fd_in_out)
		return (unlink(HEREDOC), 1);
	while (cmd->file)
	{
		if (cmd->file->token == TK_HERE_DOC)
			flag = 0;
		else if (cmd->file->token == TK_IN_R)
			flag = 1;
		cmd->file = cmd->file->next;
	}
	if (set_stdin(flag, fd_in_out, cmd, fd))
		return (free(fd_in_out), 1);
	if (set_stdout(fd_in_out, fd, cmd))
		return (free(fd_in_out), 1);
	free(fd_in_out);
	return (0);
}

int	open_heredocs(t_file *file_lst, int exit_code)
{
	while (file_lst)
	{
		if (file_lst->token == TK_HERE_DOC)
		{
			if (heredoc(file_lst, exit_code))
				return (1);
		}
		file_lst = file_lst->next;
	}
	return (0);
}

int	*open_in_out_files(t_file *file_lst)
{
	int	*fd_temp;

	fd_temp = ft_calloc(2, sizeof(*fd_temp));
	if (!fd_temp)
		return (NULL);
	while (file_lst)
	{
		if (open_in_out_files_helper(file_lst, fd_temp))
			return (free(fd_temp), NULL);
		file_lst = file_lst->next;
	}
	return (fd_temp);
}

int	open_in_out_files_helper(t_file *file_lst, int	*fd_temp)
{
	if (file_lst->token == TK_IN_R)
	{
		if (fd_temp[IN] != 0)
			close(fd_temp[IN]);
		fd_temp[IN] = open_in_file(file_lst);
		if (fd_temp[IN] == -1)
			return (1);
	}
	if (file_lst->token == TK_OUT_R || file_lst->token == TK_APP_R)
	{
		if (fd_temp[OUT] != 0)
			close(fd_temp[OUT]);
		fd_temp[OUT] = open_out_file(file_lst);
		if (fd_temp[OUT] == -1)
			return (1);
	}
	return (0);
}
