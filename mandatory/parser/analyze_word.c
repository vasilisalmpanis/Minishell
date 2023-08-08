/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:08:23 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/08 18:20:08 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	analyze_word(t_lex **lex_lst, t_cmd *new_cmd, int pos, int *arg_num)
{
	int	is_cmd;
	
	is_cmd = check_word_type(new_cmd->hd_flag, pos);
	if (is_cmd)
		new_cmd->args[(*arg_num)++] = (*lex_lst)->value; // analyze_cmd
	else
	{
		if (!(strncmp((*lex_lst)->value, "-n", ft_strlen((*lex_lst)->value))) 
			&& !(strncmp(new_cmd->cmd, "echo", ft_strlen(new_cmd->cmd)))
			&& (pos == 2 || pos == 4 && new_cmd->hd_flag == 1))
		{
			new_cmd->opts = (*lex_lst)->value;
		}
		else
			new_cmd->args[(*arg_num)++] = (*lex_lst)->value;
	}
	return (0);
}

// int	analyze_cmd()
// {
		// need to check for builtin
		// need to define command name
		// need to check if path is known

		// if path is not known
			// need to identify path 
		// check_for_path((*lex_lst)->value, new_cmd)
// }

int	check_word_type(int	hd_flag, int pos)
{
	if (pos == 1 || (pos == 3 && hd_flag == 1))
		return (1);
	else
		return (0);
}

// void	check_for_path(char *word, t_cmd *new_cmd)
// {
// 	int	i;

// 	i = -1;
// 	while (word[++i])
// 	{
// 		if (word[i] == '/')
// 		{
// 			new_cmd->path_known = 1;
// 			while (word[i + 2])
// 			{
// 				if (word[i] == '.' && word[i + 1] == 's' && word[i + 2] == 'h')
// 				{
// 					new_cmd->is_sh_script = i + 3;
// 					return ;
// 				}
// 				i++;
// 			}
// 		}
// 	}
// }
