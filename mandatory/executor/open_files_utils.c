/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:42:30 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/18 11:43:28 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_in_file(t_file *file)
{
	int	fd;

	fd = open(file->name, O_RDONLY);
	if (fd == -1)
	{
		perror(file->name);
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
	{
		perror(file->name);
		return (-1);
	}
	return (fd_temp);
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
