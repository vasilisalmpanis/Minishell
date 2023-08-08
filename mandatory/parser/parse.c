/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 18:23:58 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/08 13:02:48 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lex	*parse(t_lex *lex_lst)
{
	t_cmd	*cmd_lst;
	t_cmd	*new_cmd;
	int		id;

	id = 0;
	while (lex_lst)
	{
		new_cmd = ft_new_cmd(id++);
		if (!new_cmd)
			return (ft_cmd_lst_free(&cmd_lst), NULL); // free function to be implemented
		while (lex_lst && lex_lst->token != TK_PIPE)
		{
			if (lex_lst->token == TK_WORD)
				// analyse word
			else if (lex_lst->token == TK_HERE_DOC)
			{
				if (set_here_doc_flag(&lex_lst, new_cmd))
					// err handling malloc fail; need to free lex and cmd_lst
			}
			else if (lex_lst->token == TK_APP_R || lex_lst->token == TK_IN_R
					|| lex_lst->token == TK_OUT_R)
			{
				if (set_dir_flags(&lex_lst, new_cmd))
					// err handling malloc fail; need to free lex and cmd_lst
			}
			lex_lst = lex_lst->next;
		}
		ft_cmd_lstadd_end(&cmd_lst, new_cmd);
		lex_lst = lex_lst->next;
	}
	// free lexer lst (all values will already be freed or passed)
	return (cmd_lst);
}

int	set_here_doc_flag(t_lex **lex_lst, t_cmd *new_cmd)
{	
	new_cmd->hd_flag = 1;
	free((*lex_lst)->value);
	*lex_lst = (*lex_lst)->next;
	if ((*lex_lst)->value != TK_WORD)
		return (1);  // add err message
	new_cmd->delim = ft_strtrim((*lex_lst)->value, "\"");
	if (!new_cmd->delim)
		return (1);
	free((*lex_lst)->value);
	return (0);
}

int	set_dir_flags(t_lex **lex_lst, t_cmd *new_cmd)
{
	if ((*lex_lst)->token == TK_APP_R)
		new_cmd->app_flag = 1;
	else if ((*lex_lst)->token == TK_IN_R)
		new_cmd->in_flag = 1;
	else if ((*lex_lst)->token == TK_OUT_R)
		new_cmd->out_flag = 1;
	free((*lex_lst)->value);
	*lex_lst = (*lex_lst)->next;
	if ((*lex_lst)->value != TK_WORD)
		return (1);  // add err message
	new_cmd->file = ft_strtrim((*lex_lst)->value, "\"");
	if (!new_cmd->file)
		return (1);
	free((*lex_lst)->value);
	return (0);
}


// probably do fd allocation outside the cmd list


// here_doc: output depends on whether the heredoc is piped to sth afterwards or not
// echo hello | grep hello | << cat | grep this vs echo hello | grep hello | << eof
