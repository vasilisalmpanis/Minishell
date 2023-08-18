/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:45:22 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/18 11:03:41 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_files(t_cmd *cmd, int **fd)
{
	int	*fd_in_out;
	int	flag;

	flag = -1;
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
		return (1);
	if (set_stdout(fd_in_out, fd, cmd))
		return (1);
	free(fd_in_out);
	return (0);
}

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
			exit(EXIT_FAILURE);
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

int	*open_in_out_files(t_file *file_lst)
{
	int	*fd_temp;

	fd_temp = ft_calloc(2, sizeof(*fd_temp));
	if (!fd_temp)
		return (NULL);
	while (file_lst)
	{
		if (open_in_out_files_helper(file_lst, fd_temp))
			return (NULL);
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

int	open_in_file(t_file *file)
{
	int	fd;
	
	fd = open(file->name, O_RDONLY);
	if (fd == -1)
	{
		printf("Minishell: %s: No such file or directory\n", file->name);
		return (-1);
	}
	return (fd);
}

int	open_out_file(t_file *file)
{
	int	fd_temp;

	fd_temp = 0;
	if (file->token == TK_OUT_R)
		fd_temp = open(file->name, O_RDWR | O_CREAT | O_TRUNC, 00644);
	else
		fd_temp = open(file->name, O_RDWR | O_CREAT | O_APPEND, 00644);
	if (fd_temp == -1)
		return (-1);
	return (fd_temp);
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

int	heredoc(t_file *file, int exit_code)
{
	int		fd;
	char	*buf[2];

	fd = open(HEREDOC, O_RDWR | O_CREAT | O_TRUNC, 00644);
	if (fd == -1)
		return (1);
	while (1)
	{
		write(0, "> ", 2);
		buf[0] = get_next_line(0);
		if (!buf[0])
			return (1);
		rm_newline(&buf[0]);
		if (ft_memcmp(file->delim, buf[0], ft_strlen(file->delim) + 1) == 0)
			break ;
		buf[1] = check_expand(buf[0], -1, exit_code, 0);
		if (!buf[1])
			return (1);
		free(buf[0]);
		ft_putstr_fd_mod(buf[1], fd);
		free(buf[1]);
	}
	free(buf[0]);
	close(fd);
	return (0);
}

void	rm_newline(char **str)
{
	size_t	i;

	i = 0;
	while ((*str)[i] && (*str)[i] != '\n')
		i++;
	(*str)[i] = '\0';
}

void	ft_putstr_fd_mod(char *s, int fd)
{
	while (*s)
		write(fd, s++, 1);
	write(fd, "\n", 1);
}
