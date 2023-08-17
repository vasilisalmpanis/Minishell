/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:45:22 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/17 13:48:57 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_files(t_cmd *cmd, int **fd)
{
	int *fd_in_out;
	int	flag;
	int	fd_temp;
	
	flag = -1;
	if (open_heredocs(cmd))
		return (1);
	fd_in_out = open_in_out_files(cmd);
	if (!fd_in_out)
		return (1);
	while (cmd->file)
	{
		if (cmd->file->token == TK_HERE_DOC)
			flag = 0;
		else if (cmd->file->token == TK_IN_R)
			flag = 1;
		cmd->file = cmd->file->next;
	}
	if (flag == 0)
	{
		fd_temp = open("temp", O_RDONLY);
		if (fd_temp == -1)
			exit(EXIT_FAILURE);
		if (dup2(fd_temp, STDIN_FILENO) == -1)
		{
			printf("Error dup2\n");
			return (1);
		}
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
	{
		if (cmd->cmd_id > 0)
		{
			if (dup2(fd[cmd->cmd_id - 1][0], STDIN_FILENO) == -1)
				return (1);
		}
	}
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
	free(fd_in_out);
	return (0);
}

int	*open_in_out_files(t_cmd *cmd)
{
	int	*fd_temp;

	fd_temp = ft_calloc(2, sizeof(*fd_temp));
	if (!fd_temp)
		return (NULL);
	while (cmd->file)
	{
		if (cmd->file->token == TK_IN_R)
		{
			fd_temp[IN] = open_in_file(cmd->file);
			if (fd_temp[IN] == -1)
				return (NULL);
		}
		if (cmd->file->token == TK_OUT_R 
			|| cmd->file->token == TK_APP_R)
		{
			fd_temp[OUT] = open_out_file(cmd->file);
			if (fd_temp[OUT] == -1)
				return (NULL);
		}
		cmd->file = cmd->file->next;
	}
	return (fd_temp);
}

int	open_in_file(t_file *cmd)
{
	int	fd;
	
	fd = open(cmd->name, O_RDONLY);
	if (fd == -1)
		return (printf("Minishell: %s: No such file or directory\n", cmd->name), -1); // add proper err msg
	return (fd);
}

int	open_out_file(t_file *cmd)
{
	int	fd_temp;

	fd_temp = 0;
	if (cmd->token == TK_OUT_R)
		fd_temp = open(cmd->name, O_RDWR | O_CREAT | O_TRUNC, 00644);
	else
	{
		close(fd_temp);
		fd_temp = open(cmd->name, O_RDWR | O_CREAT | O_APPEND, 00644);
	}
	if (fd_temp == -1)
		return (-1);
	return (fd_temp);
}


int	open_heredocs(t_cmd *cmd)
{
	while (cmd->file)
	{
		if (cmd->file->token == TK_HERE_DOC)
		{
			if (heredoc(cmd->file))
				return (1);
		}
		cmd->file = cmd->file->next;
	}
	return (0);
}

int	heredoc(t_file *cmd)
{
	int		fd;
	char	*buf;
	char	*buf2;

	fd = open(HEREDOC, O_RDWR | O_CREAT | O_TRUNC, 00644);
	if (fd == -1)
		return (1);
	while (1)
	{
		write(0, "> ", 2);
		buf = get_next_line(0);
		if (!buf)
			return (1);
		rm_newline(&buf);
		if (ft_memcmp(cmd->delim, buf, ft_strlen(cmd->delim) + 1) == 0)
			break ;
		buf2 = check_expand(buf, -1, 0, 0); // should include exit code as third param
		if (!buf2)
			return (1);
		free(buf);
		ft_putstr_fd_mod(buf2, fd);
		free(buf2);
	}
	free(buf);
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



////////



// int	open_files(t_cmd *cmd)
// {
// 	int	fd_temp;

// 	fd_temp = 0;
// 	if (cmd->out_flag)
// 		fd_temp = open(cmd->out_file, O_RDWR | O_CREAT | O_TRUNC, 00644);
// 	if (cmd->app_flag)
// 	{
// 		close(fd_temp);
// 		fd_temp = open(cmd->app_file, O_RDWR | O_CREAT | O_APPEND, 00644);
// 	}
// 	if (fd_temp == -1)
// 		exit(EXIT_FAILURE);
// 	return (fd_temp);
// }

// int	open_outfiles_builtin(t_cmd *cmd, int **fd)
// {
// 	// int	fd_temp;

// 	if (cmd->next)
// 	{
// 		if (dup2(fd[cmd->cmd_id][1], STDOUT_FILENO) == -1)
// 			exit(EXIT_FAILURE);
// 	}

// 	// if (cmd->out_flag || cmd->app_flag)
// 	// {
// 	// 	fd_temp = open_files(cmd);
// 	// 	if (cmd->next)
// 	// 	{
// 	// 		if (dup2(fd[cmd->cmd_id][1], STDOUT_FILENO) == -1)
// 	// 			exit(EXIT_FAILURE);
// 	// 	}
// 	// 	else
// 	// 	{
// 	// 		if (dup2(fd_temp, STDOUT_FILENO) == -1)
// 	// 			exit(EXIT_FAILURE);
// 	// 	}
// 	// 	close(fd_temp);
// 	// }
// 	return (0);
// }

// int	open_infile(t_cmd *cmd, int **fd)
// {
// 	int	fd_temp;

// 	fd_temp = 0;
// 	if (cmd->hd_flag)
// 	{
// 		heredoc(cmd);
// 		fd_temp = open("temp", O_RDONLY);
// 		if (fd_temp == -1)
// 			exit(EXIT_FAILURE);
// 		if (dup2(fd_temp, STDIN_FILENO) == -1)
// 		{
// 			printf("Error dup2\n");
// 			return (1);
// 		}
// 		close(fd_temp);
// 		unlink(HEREDOC);
// 	}
// 	else if (cmd->in_flag)
// 	{
// 		fd_temp = open(cmd->in_file, O_RDONLY);
// 		if (fd_temp == -1)
// 			return (printf("Error infile\n"), 1); // add proper err msg
// 		if (dup2(fd_temp, STDIN_FILENO) == -1)
// 			return (1);
// 		close(fd_temp);
// 	}
// 	else
// 	{
// 		if (cmd->cmd_id > 0)
// 		{
// 			if (dup2(fd[cmd->cmd_id - 1][0], STDIN_FILENO) == -1)
// 				return (1);
// 		}
// 	}
// 	return (0);
// }

// int	open_outfile(t_cmd *cmd, int **fd)
// {
// 	int	fd_temp;

// 	if (cmd->out_flag || cmd->app_flag)
// 	{
// 		fd_temp = open_files(cmd);
// 		if (fd_temp == -1)
// 			exit(EXIT_FAILURE);
// 		if (dup2(fd_temp, STDOUT_FILENO) == -1)
// 			return (1);
// 		close(fd_temp);
// 	}
// 	else
// 	{
// 		if (cmd->next)
// 		{
// 			if (dup2(fd[cmd->cmd_id][1], STDOUT_FILENO) == -1)
// 				return (1);
// 		}
// 	}
// 	return (0);
// }
