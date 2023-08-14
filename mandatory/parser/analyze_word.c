/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:08:23 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/14 11:51:40 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	analyze_word(t_lex **lex_lst, t_cmd *new_cmd, int *arg_num, char **env_p)
{
	int	is_cmd;

	is_cmd = check_word_type(*lex_lst, new_cmd->in_flag);
	if (is_cmd)
	{
		if (analyze_cmd(lex_lst, new_cmd, arg_num, env_p))
			return (1);
	}
	else
	{
		analyze_opt(lex_lst, new_cmd);
		new_cmd->args[(*arg_num)] = ft_strdup((*lex_lst)->value);
		if (!((new_cmd->args)[(*arg_num)++]))
			return (1);
	}
	return (0);
}

int	check_word_type(t_lex *lex_lst, int in_flag)
{
	if (lex_lst->pos == 1 || (lex_lst->pos == 3 && in_flag == 1))
		return (1);
	else
		return (0);
}

int	analyze_cmd(t_lex **lex_lst, t_cmd *new_cmd, int *arg_num, char **env_p)
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
			if (get_path_name(new_cmd, env_p))
				return (1);
		}
		(new_cmd->args)[(*arg_num)] = ft_strdup(new_cmd->cmd);
		if (!(new_cmd->args[(*arg_num)++]))
			return (1);
	}
	return (0);
}

int	analyze_opt(t_lex **lex_lst, t_cmd *new_cmd)
{
	int	i;

	i = 0;
	if (ft_strncmp(new_cmd->cmd, "echo", ft_strlen(new_cmd->cmd)))
		return (1);
	if (((*lex_lst)->pos != 2
			&& !((*lex_lst)->pos == 4 && new_cmd->in_flag == 1)))
		return (1);
	if (((*lex_lst)->value)[i++] != '-')
		return (1);
	while (((*lex_lst)->value)[i])
	{
		if (((*lex_lst)->value)[i] != 'n')
			return (1);
		i++;
	}
	new_cmd->opt = 1;
	return (0);
}
