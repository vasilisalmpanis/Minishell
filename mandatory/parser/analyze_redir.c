/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 16:46:21 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/14 17:12:16 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_here_doc_flag(t_lex **lex_lst, t_cmd *new_cmd)
{
	new_cmd->hd_flag = 1;
	*lex_lst = (*lex_lst)->next;
	if ((*lex_lst)->token != TK_WORD)
	{
		ft_putstr_fd("Error: No delimiter provided for heredoc\n", 2);
		return (1);
	}
	new_cmd->delim = strdup((*lex_lst)->value);
	if (!new_cmd->delim)
		return (1);
	return (0);
}

int	set_redir_flags(t_lex **lex_lst, t_cmd *new_cmd)
{
	if ((*lex_lst)->token == TK_APP_R)
	{
		new_cmd->app_flag = 1;
	}
	else if ((*lex_lst)->token == TK_IN_R)
		new_cmd->in_flag = 1;
	else if ((*lex_lst)->token == TK_OUT_R)
		new_cmd->out_flag = 1;
	*lex_lst = (*lex_lst)->next;
	if (!(*lex_lst) || (*lex_lst)->token != TK_WORD)
	{
		ft_putstr_fd("Error: No filename provided after redirect\n", 2);
		free(new_cmd);
		return (1);
	}
	new_cmd->file = strdup((*lex_lst)->value);
	if (!new_cmd->file)
		return (1);
	return (0);
}
