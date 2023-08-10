/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:08:23 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/10 12:42:27 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	analyze_word(t_lex **lex_lst, t_cmd *new_cmd, int *arg_num, char **env_paths)
{
	int	is_cmd;
	
	is_cmd = check_word_type(*lex_lst, new_cmd->hd_flag);
	if (is_cmd)
	{
		if (analyze_cmd(lex_lst, new_cmd, arg_num, env_paths))
			return (1);
	}
	else
	{
		analyze_opt(lex_lst, new_cmd);
		new_cmd->args[(*arg_num)] = ft_strdup((*lex_lst)->value);
		if (!(new_cmd->args[(*arg_num)++]))
			return (1);
	}
	return (0);
}

int	analyze_opt(t_lex **lex_lst, t_cmd *new_cmd)
{
	int	i;

	i = 0;
	if (strncmp(new_cmd->cmd, "echo", ft_strlen(new_cmd->cmd)))
		return (1);
	if (((*lex_lst)->pos != 2 && !((*lex_lst)->pos == 4 && new_cmd->in_flag == 1)))
		return (1);
	if (((*lex_lst)->value)[i++] != '-')
		return (1);
	printf("test\n");
	while (((*lex_lst)->value)[i])
	{
		if (((*lex_lst)->value)[i] != 'n')
			return (1);
		i++;
	}
	new_cmd->opt = 1;
	return (0);
}

int	check_word_type(t_lex *lex_lst, int in_flag)
{
	if (lex_lst->pos == 1 || (lex_lst->pos == 3 && in_flag == 1))
		return (1);
	else
		return (0);
}

int	analyze_cmd(t_lex **lex_lst, t_cmd *new_cmd, int *arg_num, char **env_paths)
{
	if (check_for_builtin(lex_lst, new_cmd))
		return (1);
	if (!new_cmd->builtin)
	{
		check_for_path(lex_lst, new_cmd);
		if (get_cmd_name(lex_lst, new_cmd))
			return (1);
		if (new_cmd->path_known)
		{
			new_cmd->path = ft_strdup((*lex_lst)->value);
			if (!new_cmd->path)
				return (1);
		}
		else
		{
			new_cmd->path = get_path_name(new_cmd, env_paths);
			if (!new_cmd->path)
				return (1);
		}	
		new_cmd->args[(*arg_num)]	= ft_strdup(new_cmd->cmd);
		if (!(new_cmd->args[(*arg_num)++]))
			return (1);
	}
	return (0);	
}

int	check_for_builtin(t_lex **lex_lst, t_cmd *new_cmd)
{
	if (!(strncmp((*lex_lst)->value, "echo", ft_strlen((*lex_lst)->value))))
		new_cmd->builtin = 1;
	else if (!(strncmp((*lex_lst)->value, "cd", ft_strlen((*lex_lst)->value))))
		new_cmd->builtin = 1;
	else if (!(strncmp((*lex_lst)->value, "pwd", ft_strlen((*lex_lst)->value))))
		new_cmd->builtin = 1;
	else if (!(strncmp((*lex_lst)->value, "export", ft_strlen((*lex_lst)->value))))
		new_cmd->builtin = 1;
	else if (!(strncmp((*lex_lst)->value, "unset", ft_strlen((*lex_lst)->value))))
		new_cmd->builtin = 1;
	else if (!(strncmp((*lex_lst)->value, "env", ft_strlen((*lex_lst)->value))))
		new_cmd->builtin = 1;
	else if (!(strncmp((*lex_lst)->value, "exit", ft_strlen((*lex_lst)->value))))
		new_cmd->builtin = 1;
	if (new_cmd->builtin == 1)
	{
		new_cmd->cmd = strdup((*lex_lst)->value);
		if (!new_cmd->cmd)
			return (1);
	}
	return (0);
}

void	check_for_path(t_lex **lex_lst, t_cmd *new_cmd)
{
	int	i;

	i = -1;
	while (((*lex_lst)->value)[++i])
	{
		if (((*lex_lst)->value)[i] == '/')
		{
			new_cmd->path_known = 1;
			while (((*lex_lst)->value)[i + 2])
			{
				if (((*lex_lst)->value)[i] == '.' && ((*lex_lst)->value)[i + 1] == 's'
					&& ((*lex_lst)->value)[i + 2] == 'h')
				{
					new_cmd->is_sh_script = i + 3; //probably don't actually need flag
					return ;
				}
				i++;
			}
		}
	}
}

int	get_cmd_name(t_lex **lex_lst, t_cmd *new_cmd)
{
	char	*temp;
	
	if (!(new_cmd->path_known))
	{
		new_cmd->cmd = ft_strdup((*lex_lst)->value);
		if (!new_cmd->cmd)
			return (1);
	}
	else
	{
		temp = ft_strrchr((*lex_lst)->value, '/');
		temp++;
		new_cmd->cmd = strdup(temp);
		if (!new_cmd->cmd)
			return (1);
	}
	return (0);
}

char	*get_path_name(t_cmd *new_cmd, char **env_paths)
{
	char	*cmd_path;
	char	*cmd_mod;
	int		i;

	i = 0;
	cmd_mod = ft_strjoin("/", new_cmd->cmd);
	if (!cmd_mod)
		return (NULL);
	while (env_paths[i])
	{
		cmd_path = ft_strjoin(env_paths[i], cmd_mod);
		if (!cmd_path)
			return (free(cmd_mod), NULL);
		if (access(cmd_path, X_OK) == 0)
			return (free(cmd_mod), cmd_path);
		free(cmd_path);
		i++;
	}
	free(cmd_mod);
	return (NULL);
}
