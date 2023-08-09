/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:08:23 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/09 19:10:25 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	analyze_word(t_lex **lex_lst, t_cmd *new_cmd, int *arg_num)
{
	int	is_cmd;
	
	is_cmd = check_word_type(*lex_lst, new_cmd->hd_flag);
	if (is_cmd)
		new_cmd->args[(*arg_num)++] = (*lex_lst)->value; // analyze_cmd
	else
	{
		if (!(strncmp((*lex_lst)->value, "-n", ft_strlen((*lex_lst)->value))) 
			// && !(strncmp(new_cmd->cmd, "echo", ft_strlen(new_cmd->cmd)))
			&& ((*lex_lst)->pos == 2 || (*lex_lst)->pos == 4 && new_cmd->in_flag == 1)) // check also if all elements after -n are n, in that case it is an option
		{
			new_cmd->opt = 1;
		}
		new_cmd->args[(*arg_num)++] = (*lex_lst)->value;
	}
	return (0);
}

// int	analyze_cmd()
// {
// 		need to check for builtin
// 		need to define command name
// 		need to check if path is known

// 		if path is not known
// 			need to identify path 
// 		check_for_path((*lex_lst)->value, new_cmd)
// }

int	check_word_type(t_lex *lex_lst, int in_flag)
{
	if (lex_lst->pos == 1 || (lex_lst->pos == 3 && in_flag == 1))
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
