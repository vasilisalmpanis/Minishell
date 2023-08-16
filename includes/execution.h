/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:59:27 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/16 11:58:26 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

#include "minishell.h"

int		execute(t_cmd *cmd_lst, t_env *env_lst);
pid_t	execute_cmd(t_cmd *cmd_lst, t_env *env_lst, int **fd, int count_cmds);
int		builtin_child(t_cmd *cmd, t_env *env_lst, int **fd, int count);
int		builtin_process(t_cmd *cmd, t_env *env_lst, int **fd);
int		child_process(t_cmd *cmd_lst, t_env *env_lst, int **fd, int count);
int		check_path_existence(t_env *env_lst);
char	**new_env(t_env *env_lst);

int		count_cmds(t_cmd *cmd_lst);
int		**allocate_fds(int count);
void	create_pipes(int **fd, int count);
void	close_fds(int **fd, int count);

int		open_outfile(t_cmd *cmd, int **fd);
int		open_infile(t_cmd *cmd, int **fd);
int		open_outfiles_builtin(t_cmd *cmd, int **fd);
int		open_files(t_cmd *cmd);
void	ft_putstr_fd_mod(char *s, int fd);
int		heredoc(t_cmd *cmd);
void	rm_newline(char **str);


int		wait_for_children(t_cmd *start, int count_cmds);
int		exec_builtin(t_cmd *cmd, t_env *env_lst);


#endif