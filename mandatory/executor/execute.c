/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:38:10 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/22 17:06:00 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute(t_cmd *cmd_lst, t_env *env_lst, int exit_code)
{
	int		**fd;
	int		num_cmds;
	t_cmd	*cmd_lst_start;

	cmd_lst_start = cmd_lst;
	fd = NULL;
	num_cmds = count_cmds(cmd_lst);
	if (num_cmds > 1)
	{
		fd = allocate_fds(num_cmds);
		if (!fd)
			return (1);
		if (create_pipes(fd, num_cmds))
			return (free_mem_fd(fd, num_cmds), 1);
	}
	add_start_lst(cmd_lst);
	open_heredocs(cmd_lst, exit_code, 0);
	while (cmd_lst)
	{
		cmd_lst->pid = execute_cmd(cmd_lst, env_lst, fd, num_cmds);
		cmd_lst = cmd_lst->next;
	}
	close_fds(fd, num_cmds);
	if (!(num_cmds == 1 && cmd_lst_start->builtin))
		exit_code = wait_for_children(cmd_lst_start);
	else
		exit_code = (int)cmd_lst_start->pid;
	free_mem_fd(fd, num_cmds);
	return (exit_code);
}

pid_t	execute_cmd(t_cmd *cmd_lst, t_env *env_lst, int **fd, int count_cmds)
{
	pid_t	pid;

	if (count_cmds == 1 && cmd_lst->builtin)
		return (builtin_process(cmd_lst, env_lst, fd));
	else 
	{
		signal(SIGINT, handle_sigint_child);
		pid = fork();
		if (pid < 0)
			return (1);
		if (pid == 0)
		{
			if (cmd_lst->builtin)
				builtin_child(cmd_lst, env_lst, fd, count_cmds);
			else
				child_process(cmd_lst, env_lst, fd, count_cmds);
		}
	}
	return (pid);
}

int	builtin_child(t_cmd *cmd, t_env *env_lst, int **fd, int count)
{
	int	exit_code;
	int	fd_stdout;

	exit_code = 0;
	fd_stdout = dup(STDOUT_FILENO);
	if (open_files(cmd, fd))
		exit(EXIT_FAILURE);
	close_fds(fd, count);
	if (!cmd->args)
		exit(EXIT_FAILURE);
	exit_code = exec_builtin(cmd, env_lst);
	if (dup2(fd_stdout, STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	free_mem_fd(fd, count);
	ft_env_free((&env_lst));
	ft_cmd_lst_free_child(cmd->start);
	exit(exit_code);
}

int	builtin_process(t_cmd *cmd, t_env *env_lst, int **fd)
{
	int	exit_code;
	int	fd_stdout;

	fd_stdout = dup(STDOUT_FILENO);
	if (open_files(cmd, fd))
		return (1);
	exit_code = exec_builtin(cmd, env_lst);
	if (dup2(fd_stdout, STDOUT_FILENO) == -1)
		return (ft_putstr_fd("Error stdout", 2), 1);
	return (exit_code);
}

void	ft_print_error_msg(char *msg, int exit_code)
{
	ft_putstr_fd(msg, 2);
	exit(exit_code);
}

int	child_process(t_cmd *cmd, t_env *env_lst, int **fd, int count)
{
	char	**env_array;

	if (open_files(cmd, fd))
		exit(EXIT_FAILURE);
	close_fds(fd, count);
	if (!check_path_existence(env_lst) && !(cmd->path_known))
	{
		printf("no path found\n");
		exit(errno);
	}
	if (!cmd->path)
		ft_print_error_msg(" command not found\n", 127);
	if (access(cmd->path, F_OK) == -1)
	{
		perror("minishell");
		exit(127);
	}
	if (access(cmd->path, X_OK) == -1)
	{
		perror("minishell");
		exit(126);
	}
	env_array = new_env(env_lst);
	if (!env_array)
		exit(EXIT_FAILURE);
	if (!cmd->args)
		exit(EXIT_FAILURE);
	free_mem_fd(fd, count);
	ft_env_free((&env_lst));
	if (execve(cmd->path, cmd->args, env_array) == -1)
		ft_print_error_msg(" is a directory\n", 126);
	return (0);
}
