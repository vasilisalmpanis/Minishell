/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 14:58:04 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/15 15:01:36 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_cmds(t_cmd *cmd_lst)
{
	int	count;

	count = 0;
	while (cmd_lst)
	{
		count++;
		cmd_lst = cmd_lst->next;
	}
	return (count);
}

int	**allocate_fds(int count)
{
	int	**fd;
	int	i;

	i = 0;
	fd = malloc((count - 1) * sizeof(*fd));
	if (!fd)
		return (NULL);
	while (i < count - 1)
	{
		fd[i] = malloc(2 * sizeof(**fd)); 
		if (!fd[i++])
			return (NULL); // free fds allocated so far; may convert ft_free to void
	}
	return (fd);
}

void	create_pipes(int **fd, int count)
{
	int	i;

	i = 0;
	while (i < count - 1)
	{
		if (pipe(fd[i]) == -1)
			exit(EXIT_FAILURE); // check what bash is doing in that case
		i++;
	}
}

void	close_fds(int **fd, int count)
{
	int	i;

	i = 0;
	while (i < count - 1)
	{
		close(fd[i][0]); // error check?
		close(fd[i][1]);
		i++;
	}
}
