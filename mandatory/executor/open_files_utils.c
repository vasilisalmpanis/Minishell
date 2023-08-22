/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:42:30 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/22 16:54:38 by mamesser         ###   ########.fr       */
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
