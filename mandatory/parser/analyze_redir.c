/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 16:46:21 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/16 14:52:37 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_here_doc_flag(t_lex **lex_lst, t_cmd *new_cmd)
{
	new_cmd->hd_flag = 1;
	if (new_cmd->in_flag)
		new_cmd->in_flag = 0;
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
		if (set_filename(lex_lst, new_cmd, (*lex_lst)->token))
			return (1);
	}
	else if ((*lex_lst)->token == TK_IN_R)
	{
		new_cmd->in_flag = 1;
		if (new_cmd->hd_flag)
			new_cmd->hd_flag = 0;
		if (set_filename(lex_lst, new_cmd, (*lex_lst)->token))
			return (1);
	}
	else if ((*lex_lst)->token == TK_OUT_R)
	{
		new_cmd->out_flag = 1;
		if (set_filename(lex_lst, new_cmd, (*lex_lst)->token))
			return (1);
	}
	return (0);
}

int	set_filename(t_lex **lex_lst, t_cmd *new_cmd, int token)
{
	*lex_lst = (*lex_lst)->next;
	if (!(*lex_lst) || (*lex_lst)->token != TK_WORD)
	{
		printf("Minishell: syntax error near unexpected token '%c'\n", (*lex_lst)->token);
		free(new_cmd);
		return (1);
	}
	if (token == TK_APP_R)
	{
		if (new_cmd->app_file)
			free(new_cmd->app_file);
		new_cmd->app_file = strdup((*lex_lst)->value);
		if (!new_cmd->app_file)
			return (1);
	}
	if (token == TK_OUT_R)
	{
		if (new_cmd->out_file)
			free(new_cmd->out_file);
		new_cmd->out_file = strdup((*lex_lst)->value);
		if (!new_cmd->out_file)
			return (1);
	}
	else if (token == TK_IN_R)
	{
		if (new_cmd->in_file)
			free(new_cmd->in_file);
		new_cmd->in_file = strdup((*lex_lst)->value);
		if (!new_cmd->in_file)
			return (1);
	}
	return (0);
}