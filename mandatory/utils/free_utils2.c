/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 12:54:21 by valmpani          #+#    #+#             */
/*   Updated: 2023/08/23 16:38:04 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_mem_fd(int **fd, int num_cmds)
{
	int	i;

	i = 0;
	while (i < num_cmds - 1)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
}

void	free_stuff(t_env **env_lst, t_cmd *cmd, char **env_array)
{
	ft_env_free(env_lst);
	ft_cmd_lst_free_child(cmd);
	if (env_array)
		ft_free(env_array);
}
