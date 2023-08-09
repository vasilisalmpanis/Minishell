/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 18:23:58 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/09 19:10:58 by mamesser         ###   ########.fr       */
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

	id = 0;
	cmd_lst = NULL;
	while (lex_lst)
	{
		new_cmd = ft_new_cmd(id++);
		// if (!new_cmd)
		// 	return (ft_cmd_lst_free(&cmd_lst), NULL); // free function to be implemented + free lex
		arg_num = 0;
		if (allocate_args(lex_lst, new_cmd))
			return (NULL); // also: free cmd_lst and lex
		while (lex_lst && lex_lst->token != TK_PIPE)
		{
			analyze_token(&lex_lst, new_cmd, &arg_num);
				// malloc err hanlding
			lex_lst = lex_lst->next;
		}
		new_cmd->args[arg_num] = NULL;
		ft_cmd_lstadd_end(&cmd_lst, new_cmd);
		if (lex_lst)
			lex_lst = lex_lst->next;
	}
	// free lexer lst (all values will already be freed or passed)
	return (cmd_lst);
}

int	allocate_args(t_lex *lex_lst, t_cmd *new_cmd)
{
	int		arg_num;
	t_lex	**start_lst;

	start_lst = &lex_lst;
	arg_num = 0;
	while (*start_lst && (*start_lst)->token != TK_PIPE)
	{
		if ((*start_lst)->token == TK_WORD)
			arg_num++;
		else if ((*start_lst)->token == TK_IN_R || (*start_lst)->token == TK_OUT_R
			|| (*start_lst)->token == TK_APP_R || (*start_lst)->token == TK_HERE_DOC)
		{
			arg_num -= 1;
		}
		
		start_lst = &(*start_lst)->next;
	}
	new_cmd->args = malloc((arg_num + 1) * sizeof((*new_cmd->args)));
	if (!new_cmd->args)
		return (1);
	return (0);
}


int	analyze_token(t_lex **lex_lst, t_cmd *new_cmd, int *arg_num)
{
	if ((*lex_lst)->token == TK_WORD)
		analyze_word(lex_lst, new_cmd, arg_num);
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

// void	ft_show_tab(t_lex *list)
// {
// 	while (list)
// 	{
// 		ft_putstr_fd(list->value, 1);
// 		write(1, "\n", 1);
// 		printf("token: %c\n", list->token);
// 		printf("position: %d\n", list->pos);
// 		// write(1, "\n", 1);
// 		list = list->next;
// 	}
// }

// void	ft_show_tab2(t_cmd *list)
// {
// 	write(1, "\n", 1);
// 	while (list)
// 	{
// 		printf("cmd id: %d\n", list->cmd_id);
// 		printf("hd_flag: %d\n", list->hd_flag);
// 		printf("in_flag: %d\n", list->in_flag);
// 		printf("out_flag: %d\n", list->out_flag);
// 		printf("file: %s\n", list->file);
// 		printf("delim: %s\n", list->delim);
// 		printf("opts: %d\n", list->opt);
// 		printf("args[0]: %s\n", list->args[0]);
// 		printf("args[1]: %s\n", list->args[1]);
// 		write(1, "\n", 1);
// 		list = list->next;
// 	}
// }

// int	main(void)
// {
// 	t_lex 	*lex_lst;
// 	t_cmd	*cmd_lst;
// 	char	input[] = "echo \"Hello World\" | cat << eof | echo > file2 | echo -n \"Hello\"\0";

// 	lex_lst = lex(input);
// 	ft_show_tab(lex_lst);
	
// 	cmd_lst = parse(lex_lst);
// 	ft_show_tab2(cmd_lst);
	
	
// }