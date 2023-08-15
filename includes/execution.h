/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:59:27 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/15 13:11:23 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

#include "minishell.h"

int	execute(t_cmd *cmd_lst, t_env *env_lst);
pid_t	execute_cmd(t_cmd *cmd_lst, t_env *env_lst, int **fd, int count_cmds);
int	**allocate_fds(int count);
int	count_cmds(t_cmd *cmd_lst);
void	create_pipes(int **fd, int count);
int		child_process(t_cmd *cmd_lst, t_env *env_lst, int **fd, int count);
void	close_fds(int **fd, int count);
int	wait_for_children(t_cmd *start, int count_cmds);
int	exec_builtin(t_cmd *cmd, t_env *env_lst);
int	builtin_child(t_cmd *cmd, t_env *env_lst, int **fd, int count);


#endif