/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmpani <valmpanis@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 13:38:10 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/18 11:07:33 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute(t_cmd *cmd_lst, t_env *env_lst, int exit_code)
{
	int		**fd;
	int		num_cmds;
	t_cmd	*cmd_lst_start;

	cmd_lst_start = cmd_lst;
	num_cmds = count_cmds(cmd_lst);
	fd = allocate_fds(num_cmds);
	if (!fd)
		return (1);
	if (create_pipes(fd, num_cmds))
		return (1);
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
	return (exit_code);
}

pid_t	execute_cmd(t_cmd *cmd_lst, t_env *env_lst, int **fd, int count_cmds)
{
	pid_t	pid;

	if (count_cmds == 1 && cmd_lst->builtin)
		return (builtin_process(cmd_lst, env_lst, fd)); // don't create child process; execute builtin return -1?
	else 
	{
		signal(SIGINT, handle_sigint_child);
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

int	child_process(t_cmd *cmd, t_env *env_lst, int **fd, int count)
{
	char	**env_array;
	
	if (open_files(cmd, fd))
		exit(EXIT_FAILURE);
	close_fds(fd, count);
	if (!check_path_existence(env_lst))
	{
		printf("no path found\n");
		exit(127);
	}
	env_array = new_env(env_lst);
	if (!env_array)
		exit(EXIT_FAILURE); // error message
	if (!cmd->args)
		exit(EXIT_FAILURE); // error message (printf("No args provided\n"), 1);
	if (execve(cmd->path, cmd->args, NULL) == -1)
		exit(EXIT_FAILURE);
	return (0);
}

char	**new_env(t_env *env_lst)
{
	char	**env_array;
	char	*temp;
	int		len;
	int		i;

	i = -1;
	len = env_lst_size(env_lst);
	env_array = ft_calloc(len + 1, sizeof(*env_array));
	if (!env_array)
		return (NULL);
	while (env_lst)
	{
		if (env_lst->value[0] != '\0')
		{
			temp = ft_strjoin(env_lst->key, "=");
			if (!temp)
				return (ft_free(env_array), NULL);
			env_array[++i] = ft_strjoin(temp, env_lst->value);
			if (!env_array[i])
				return (ft_free(env_array), NULL);
			free(temp);
		}
		env_lst = env_lst->next;
	}
	return (env_array);
}

int	check_path_existence(t_env *env_lst)
{
	while (env_lst)
	{
		if (!(ft_strncmp(env_lst->key, "PATH", ft_strlen(env_lst->key))))
			return (1);
		env_lst = env_lst->next;
	}
	return (0);
}
