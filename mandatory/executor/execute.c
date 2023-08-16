/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmpani <valmpanis@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:38:10 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/15 21:18:52 by valmpani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute(t_cmd *cmd_lst, t_env *env_lst)
{
	int		**fd;
	int		num_cmds;
	t_cmd	*cmd_lst_start;

	cmd_lst_start = cmd_lst;
	num_cmds = count_cmds(cmd_lst);
	fd = allocate_fds(num_cmds);
	if (!fd)
		return (1);
	create_pipes(fd, num_cmds);
	while (cmd_lst)
	{
		cmd_lst->pid = execute_cmd(cmd_lst, env_lst, fd, num_cmds);
		cmd_lst = cmd_lst->next;
	}
	close_fds(fd, num_cmds);
	wait_for_children(cmd_lst_start, num_cmds);
	return (0); // probably rather return last exit code
}

pid_t	execute_cmd(t_cmd *cmd_lst, t_env *env_lst, int **fd, int count_cmds)
{
	pid_t	pid;

	if (count_cmds == 1 && cmd_lst->builtin)
		return (builtin_process(cmd_lst, env_lst, fd), -1); // don't create child process; execute builtin return -1?
	else 
	{
		pid = fork();
		if (pid < 0)
			return (1);
		if (pid == 0)
		{
			if (cmd_lst->builtin)
				builtin_child(cmd_lst, env_lst, fd, count_cmds); // function for builtins
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

	fd_stdout = dup(STDOUT_FILENO);
	open_outfiles_builtin(cmd, fd);
	close_fds(fd, count);
	if (!cmd->args)
		exit(EXIT_FAILURE);
	exit_code = exec_builtin(cmd, env_lst);
	if (dup2(fd_stdout, STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	exit(0);
}

int	builtin_process(t_cmd *cmd, t_env *env_lst, int **fd)
{
	int	exit_code;
	int	fd_stdout;

	fd_stdout = dup(STDOUT_FILENO);
	open_outfiles_builtin(cmd, fd);
	exit_code = exec_builtin(cmd, env_lst);
	if (dup2(fd_stdout, STDOUT_FILENO) == -1)
		return (ft_putstr_fd("Error stdout", 2), 1);
	return (0);
}

int	child_process(t_cmd *cmd, t_env *env_lst, int **fd, int count)
{
	(void)env_lst;
	open_infile(cmd, fd);
	open_outfile(cmd, fd);
	close_fds(fd, count);
	// function to check if PATH exists; if not give error
	// if (!cmd_lst->path)
	// 	return (printf("Error: path not known\n"), 1);
	if (!cmd->args)
	{
		printf("No args provided\n");
		exit(1);
	}
	if (execve(cmd->path, cmd->args, NULL) == -1)
		exit(EXIT_FAILURE);
	exit (0);
}
