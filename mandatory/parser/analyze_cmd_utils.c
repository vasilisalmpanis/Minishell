/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_cmd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 16:56:18 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/10 16:59:37 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_for_builtin(t_lex **lex_lst, t_cmd *new_cmd)
{
	if (!(strncmp((*lex_lst)->value, "echo", ft_strlen((*lex_lst)->value))))
		new_cmd->builtin = 1;
	else if (!(strncmp((*lex_lst)->value, "cd", ft_strlen((*lex_lst)->value))))
		new_cmd->builtin = 1;
	else if (!(strncmp((*lex_lst)->value, "pwd", ft_strlen((*lex_lst)->value))))
		new_cmd->builtin = 1;
	else if (!(strncmp((*lex_lst)->value, 
				"export", ft_strlen((*lex_lst)->value))))
		new_cmd->builtin = 1;
	else if (!(strncmp((*lex_lst)->value, 
				"unset", ft_strlen((*lex_lst)->value))))
		new_cmd->builtin = 1;
	else if (!(strncmp((*lex_lst)->value, "env", ft_strlen((*lex_lst)->value))))
		new_cmd->builtin = 1;
	else if (!(strncmp((*lex_lst)->value, 
				"exit", ft_strlen((*lex_lst)->value))))
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
				if (((*lex_lst)->value)[i] == '.'
					&& ((*lex_lst)->value)[i + 1] == 's'
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
