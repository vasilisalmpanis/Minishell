/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 18:23:58 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/08 18:36:08 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// probably do fd allocation outside the cmd list

// here_doc: output depends on whether the heredoc is piped to sth afterwards or not
// echo hello | grep hello | << cat | grep this vs echo hello | grep hello | << eof
// in the executor we can just check if there is another node after the here_doc cmd_node

// ISSUE: need to allocate memory for **args (need to know number of args --> how to calc? --> 
// or just three and the second one is bound together?)

t_cmd	*parse(t_lex *lex_lst)
{
	t_cmd	*cmd_lst;
	t_cmd	*new_cmd;
	int		id;
	int		arg_num;
	int		pos;

	id = 0;
	cmd_lst = NULL;
	while (lex_lst)
	{
		new_cmd = ft_new_cmd(id++);
		// if (!new_cmd)
		// 	return (ft_cmd_lst_free(&cmd_lst), NULL); // free function to be implemented
		pos = 1;
		arg_num = 0;
		while (lex_lst && lex_lst->token != TK_PIPE)
		{
			analyze_token(&lex_lst, new_cmd, &pos, &arg_num);
				// malloc err hanlding
			lex_lst = lex_lst->next;
		}
		// new_cmd->args[arg_num] = NULL;
		ft_cmd_lstadd_end(&cmd_lst, new_cmd);
		if (lex_lst)
			lex_lst = lex_lst->next;
	}
	// free lexer lst (all values will already be freed or passed)
	return (cmd_lst);
}

int	analyze_token(t_lex **lex_lst, t_cmd *new_cmd, int *pos, int *arg_num)
{
	if ((*lex_lst)->token == TK_WORD)
		analyze_word(lex_lst, new_cmd, *pos, arg_num);
	else if ((*lex_lst)->token == TK_HERE_DOC)
	{
		if (set_here_doc_flag(lex_lst, new_cmd))
			return (1); //err handling malloc fail; need to free lex and cmd_lst
	}
	else if ((*lex_lst)->token == TK_APP_R || (*lex_lst)->token == TK_IN_R
			|| (*lex_lst)->token == TK_OUT_R)
	{
		if (set_redir_flags(lex_lst, new_cmd))
			return (1); // err handling malloc fail; need to free lex and cmd_lst
	}
	(*pos)++;
	return (0);
}

int	set_here_doc_flag(t_lex **lex_lst, t_cmd *new_cmd)
{	
	new_cmd->hd_flag = 1;
	free((*lex_lst)->value);
	*lex_lst = (*lex_lst)->next;
	if ((*lex_lst)->token != TK_WORD)
		return (1);  // add err message, free?
	new_cmd->delim = (*lex_lst)->value;
	return (0);
}

int	set_redir_flags(t_lex **lex_lst, t_cmd *new_cmd)
{
	if ((*lex_lst)->token == TK_APP_R)
		new_cmd->app_flag = 1;
	else if ((*lex_lst)->token == TK_IN_R)
		new_cmd->in_flag = 1;
	else if ((*lex_lst)->token == TK_OUT_R)
		new_cmd->out_flag = 1;
	free((*lex_lst)->value);
	*lex_lst = (*lex_lst)->next;
	if ((*lex_lst)->token != TK_WORD)
		return (1);  // add err message, free?
	new_cmd->file = (*lex_lst)->value;
	return (0);
}




// TESTING //
// gcc -fsanitize=address parse.c ../../libft/libft.a ../lexer/lexer.c ../utils/linked_lst.c ../lexer/expansion.c ../utils/utils.c ./analyze_word.c 

void	ft_show_tab(t_lex *list)
{
	while (list)
	{
		ft_putstr_fd(list->value, 1);
		write(1, "\n", 1);
		printf("token: %c\n", list->token);
		// write(1, "\n", 1);
		list = list->next;
	}
}

void	ft_show_tab2(t_cmd *list)
{
	write(1, "\n", 1);
	while (list)
	{
		printf("cmd id: %d\n", list->cmd_id);
		printf("hd_flag: %d\n", list->hd_flag);
		printf("in_flag: %d\n", list->in_flag);
		printf("out_flag: %d\n", list->out_flag);
		printf("file: %s\n", list->file);
		printf("delim: %s\n", list->delim);
		printf("opts: %s\n", list->opts);
		printf("args[0]: %s\n", list->args[0]);
		// printf("word: %s\n", list->out_);
		// ft_putstr_fd(list->cmd_id, 1);
		// write(1, "\n", 1);
		// printf("token: %c\n", list->token);
		write(1, "\n", 1);
		list = list->next;
	}
}

int	main(void)
{
	t_lex 	*lex_lst;
	t_cmd	*cmd_lst;
	char	input[] = "cat << eof | echo > file2 | \"hello | test\"\0";

	lex_lst = lex(input);
	ft_show_tab(lex_lst);
	
	cmd_lst = parse(lex_lst);
	ft_show_tab2(cmd_lst);
	
	
}