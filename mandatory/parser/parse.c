/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 18:23:58 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/10 13:10:13 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// probably do fd allocation outside the cmd list

// here_doc: output depends on whether the heredoc is piped to sth afterwards or not
// echo hello | grep hello | << cat | grep this vs echo hello | grep hello | << eof
// in the executor we can just check if there is another node after the here_doc cmd_node


t_cmd	*parse(t_lex *lex_lst, char **env_paths)
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
		if (!new_cmd)
			return (free_cmd_and_lex(&cmd_lst, &lex_lst), NULL);
		arg_num = 0;
		if (allocate_args(lex_lst, new_cmd))
			return (free_cmd_and_lex(&cmd_lst, &lex_lst), NULL);
		while (lex_lst && lex_lst->token != TK_PIPE)
		{
			if (analyze_token(&lex_lst, new_cmd, &arg_num, env_paths))
				return (free_cmd_and_lex(&cmd_lst, &lex_lst), NULL);
			lex_lst = lex_lst->next;
		}
		new_cmd->args[arg_num] = NULL;
		ft_cmd_lstadd_end(&cmd_lst, new_cmd);
		if (lex_lst)
			lex_lst = lex_lst->next;
	}
	ft_lst_free(&lex_lst);
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


int	analyze_token(t_lex **lex_lst, t_cmd *new_cmd, int *arg_num, char **env_paths)
{
	if ((*lex_lst)->token == TK_WORD)
	{
		if (analyze_word(lex_lst, new_cmd, arg_num, env_paths))
			return (1);
	}
	else if ((*lex_lst)->token == TK_HERE_DOC)
	{
		if (set_here_doc_flag(lex_lst, new_cmd))
			return (1);
	}
	else if ((*lex_lst)->token == TK_APP_R || (*lex_lst)->token == TK_IN_R
			|| (*lex_lst)->token == TK_OUT_R)
	{
		if (set_redir_flags(lex_lst, new_cmd))
			return (1);
	}
	return (0);
}

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
		new_cmd->app_flag = 1;
	else if ((*lex_lst)->token == TK_IN_R)
		new_cmd->in_flag = 1;
	else if ((*lex_lst)->token == TK_OUT_R)
		new_cmd->out_flag = 1;
	*lex_lst = (*lex_lst)->next;
	if ((*lex_lst)->token != TK_WORD)
	{
		ft_putstr_fd("Error: No filename provided after redirect\n", 2);
		return (1);
	}
	new_cmd->file = strdup((*lex_lst)->value);
	if (!new_cmd->file)
		return (1);
	return (0);
}




// TESTING //
// gcc -fsanitize=address parse.c ../../libft/libft.a ../lexer/lexer.c ../utils/linked_lst.c ../lexer/expansion.c ../utils/utils.c ./analyze_word.c 

char	**get_env_paths(char **envp)
{
	char	**env_paths;
	char	*path_var;
	int		i;

	i = 0;
	if (envp && *envp)
	{
		while (envp[i] && !(ft_strnstr(envp[i], "PATH=", 5)))
			i++;
		if (!envp[i])
			return (NULL);
		path_var = ft_strtrim(envp[i], "PATH=");
		if (!path_var)
			return (NULL);
		env_paths = ft_split(path_var, ':');
		if (!env_paths)
			return (NULL);
		free(path_var);
		return (env_paths);
	}
	return (NULL);
}


void	ft_show_tab(t_lex *list)
{
	while (list)
	{
		ft_putstr_fd(list->value, 1);
		write(1, "\n", 1);
		printf("token: %c\n", list->token);
		printf("position: %d\n", list->pos);
		// write(1, "\n", 1);
		list = list->next;
	}
}

void	ft_show_tab2(t_cmd *list)
{
	int	i;
	
	write(1, "\n", 1);
	while (list)
	{
		printf("cmd id: %d\n", list->cmd_id);
		printf("hd_flag: %d\n", list->hd_flag);
		printf("in_flag: %d\n", list->in_flag);
		printf("out_flag: %d\n", list->out_flag);
		printf("file: %s\n", list->file);
		printf("delim: %s\n", list->delim);
		printf("opts: %d\n", list->opt);
		printf("cmd: %s\n", list->cmd);
		printf("builtin: %d\n", list->builtin);
		printf("path: %s\n", list->path);
		i = 0;
		while (list->args[i])
		{
			printf("args[%d]: %s\n", i, list->args[i]);
			i++;
		}
		// printf("args[1]: %s\n", list->args[1]);
		write(1, "\n", 1);
		list = list->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_lex 	*lex_lst;
	t_cmd	*cmd_lst;
	t_cmd	*start_lst;
	int		i = 1;
	char	**env_paths;
	char	input[] = "/bin/echo -n hello | ./test/script.sh | echo -n Hello | echo -nnnnnnn lol | echo -nnnf what | grep -n what\0";

	(void)argc;
	(void)argv;
	lex_lst = lex(input);
	ft_show_tab(lex_lst);
	
	env_paths = get_env_paths(envp);
	cmd_lst = parse(lex_lst, env_paths);
	start_lst = cmd_lst;
	ft_show_tab2(cmd_lst);

	while (env_paths[++i])
		free(env_paths[i]);
	free(env_paths);
	ft_cmd_lst_free(&start_lst);
}