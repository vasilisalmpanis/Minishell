/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:38:10 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/15 12:43:43 by mamesser         ###   ########.fr       */
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
	// wait_for_children(cmd_lst_start, num_cmds);
	return (0); // probably rather return last exit code
}


pid_t	execute_cmd(t_cmd *cmd_lst, t_env *env_lst, int **fd, int count_cmds)
{
	pid_t	pid;
	
	if (count_cmds == 1 && cmd_lst->builtin)
		return (exec_builtin(cmd_lst, env_lst), -1); // don't create child process; execute builtin return -1?
	else 
	{
		pid = fork();
		if (pid < 0)
			return (1);
		if (pid == 0)
		{
			if (cmd_lst->builtin)
				return (-1); // function for builtins
			else
				child_process(cmd_lst, env_lst, fd, count_cmds);
		}
			///
	}
	return (pid);
}

int	exec_builtin(t_cmd *cmd, t_env *env_lst)
{
	int	fd_temp;
	int	exit_code;
	int	fd_stdout;

	fd_stdout = dup(STDOUT_FILENO);
	if (cmd->out_flag || cmd->app_flag) // check for append, open depends on it
	{
		if (cmd->out_flag)
			fd_temp = open(cmd->out_file, O_RDWR | O_CREAT | O_TRUNC, 00644);
		if (cmd->app_flag)
		{
			close(fd_temp);
			fd_temp = open(cmd->app_file, O_RDWR | O_CREAT | O_APPEND, 00644);
		}
		if (fd_temp == -1)
			return (printf("Error\n"), 1); // add proper err msg
		if (dup2(fd_temp, STDOUT_FILENO) == -1)
			return (1);
		close(fd_temp);
	}
	if (!ft_strncmp(cmd->cmd, "echo", ft_strlen(cmd->cmd)))
		exit_code = echo(cmd);
	else if (!ft_strncmp(cmd->cmd, "pwd", ft_strlen(cmd->cmd)))
		exit_code = pwd();
	else if (!ft_strncmp(cmd->cmd, "env", ft_strlen(cmd->cmd)))
		exit_code = env(env_lst, cmd);
	else if (!ft_strncmp(cmd->cmd, "cd", ft_strlen(cmd->cmd)))
		exit_code = cd_dir(cmd, env_lst);
	else if (!ft_strncmp(cmd->cmd, "export", ft_strlen(cmd->cmd)))
		exit_code = export(&env_lst, cmd);
	else if (!ft_strncmp(cmd->cmd, "unset", ft_strlen(cmd->cmd)))
		exit_code = unset(&env_lst, cmd);
	if (dup2(fd_stdout, STDOUT_FILENO) == -1)
			return (ft_putstr_fd("Error stdout", 2), 1);
	return (0);
}

int	child_process(t_cmd *cmd_lst, t_env *env_lst, int **fd, int count)
{
	int	fd_temp;

	(void)env_lst;
	if (cmd_lst->in_flag)
	{
		fd_temp = open(cmd_lst->in_file, O_RDONLY);
		if (fd_temp == -1)
			return (printf("Error infile\n"), 1); // add proper err msg
		if (dup2(fd_temp, STDIN_FILENO) == -1)
			return (1);
		close(fd_temp);
	}
	else
	{
		if (cmd_lst->cmd_id > 0)
		{
			if (dup2(fd[cmd_lst->cmd_id - 1][0], STDIN_FILENO) == -1)
				return (1);
		}
	}
	if (cmd_lst->out_flag) // check for append, open depends on it
	{
		fd_temp = open(cmd_lst->out_file, O_RDWR | O_CREAT | O_TRUNC, 00644);
		if (fd_temp == -1)
			return (printf("Error outfile\n"), 1); // add proper err msg
		if (dup2(fd_temp, STDOUT_FILENO) == -1)
			return (1);
		close(fd_temp);
	}
	else
	{
		if (cmd_lst->next)
		{
			if (dup2(fd[cmd_lst->cmd_id][1], STDOUT_FILENO) == -1)
				return (1);
		}
	}
	close_fds(fd, count);
	// function to check if PATH exists; if not give error
	// if (!cmd_lst->path)
	// 	return (printf("Error: path not known\n"), 1);
	if (!cmd_lst->args)
		return (printf("No args provided\n"), 1);
	if (execve(cmd_lst->path, cmd_lst->args, NULL) == -1)
		exit(EXIT_FAILURE);
	return (0);
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

int	wait_for_children(t_cmd *start, int count_cmds)
{
	int		status;
	int		exit_code;

	status = 0;
	exit_code = 0;
	(void)count_cmds;
	while (start->next)
	{
		// if (count_cmds == 1 && start->builtin)
		waitpid(start->pid, NULL, 0);
		start = start->next;
	}
	if (waitpid(start->pid, &status, 0) == -1)
		return(EXIT_FAILURE); // store that in some variable
	if (WIFEXITED(status))
	{
		exit_code = WEXITSTATUS(status);
		if (exit_code != 0)
			return(exit_code); // store that in some variable
	}
	return (0);
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
