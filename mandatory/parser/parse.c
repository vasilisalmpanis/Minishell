/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 18:23:58 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/10 17:10:50 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// here_doc: output depends on whether the heredoc is piped to sth afterwards or not
// echo hello | grep hello | << cat | grep this vs echo hello | grep hello | << eof
// in the executor we can just check if there is another node after the here_doc cmd_node

t_cmd	*parser(t_lex *lex_lst, char **env_paths)
{
	t_cmd	*cmd_lst;
	t_cmd	*cmd_lst_start;
	t_cmd	*new_cmd;

	cmd_lst = NULL;
	cmd_lst_start = cmd_lst;
	// probably do fd allocation here; outside the cmd list / or in main.c after lexing?
	if (parse_tokens(lex_lst, &cmd_lst, env_paths))
		return (free_cmd_and_lex(&cmd_lst_start, &lex_lst), NULL);
	ft_lst_free(&lex_lst);
	return (cmd_lst);
}

int	parse_tokens(t_lex *lex_lst, t_cmd **cmd_lst, char **env_paths)
{
	t_cmd	*new_cmd;
	int		arg_num;
	int		id;

	id = 0;
	while (lex_lst)
	{
		new_cmd = ft_new_cmd(id++);
		if (!new_cmd)
			return (1);
		arg_num = 0;
		if (allocate_args(lex_lst, new_cmd))
			return (1);
		while (lex_lst && lex_lst->token != TK_PIPE)
		{
			if (analyze_token(&lex_lst, new_cmd, &arg_num, env_paths))
				return (1);
			lex_lst = lex_lst->next;
		}
		(new_cmd->args)[arg_num] = NULL;
		ft_cmd_lstadd_end(cmd_lst, new_cmd);
		if (lex_lst)
			lex_lst = lex_lst->next;
	}
	return (0);
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
		else if ((*start_lst)->token == TK_IN_R
			|| (*start_lst)->token == TK_OUT_R
			|| (*start_lst)->token == TK_APP_R
			|| (*start_lst)->token == TK_HERE_DOC)
		{
			arg_num -= 1;
		}
		start_lst = &(*start_lst)->next;
	}
	new_cmd->args = malloc((arg_num + 1) * sizeof(char *)); // probably allocated too much memory in case of builtin
	if (!new_cmd->args)
		return (1);
	return (0);
}

int	analyze_token(t_lex **lex_lst, t_cmd *new_cmd, int *arg_num, char **env_p)
{
	if ((*lex_lst)->token == TK_WORD)
	{
		if (analyze_word(lex_lst, new_cmd, arg_num, env_p))
			return (1);
	}
	else if ((*lex_lst)->token == TK_HERE_DOC)
	{
		if (set_here_doc_flag(lex_lst, new_cmd))
			return (1);
	}
	else if ((*lex_lst)->token == TK_APP_R
		|| (*lex_lst)->token == TK_IN_R
		|| (*lex_lst)->token == TK_OUT_R)
	{
		if (set_redir_flags(lex_lst, new_cmd))
			return (1);
	}
	return (0);
}

// TESTING //
// gcc -fsanitize=address parse.c ../../libft/libft.a ../lexer/lexer.c ../utils/linked_lst.c ../lexer/expansion.c ../utils/utils.c ./analyze_word.c 

// char	**get_env_paths(char **envp)
// {
// 	char	**env_paths;
// 	char	*path_var;
// 	int		i;

// 	i = 0;
// 	if (envp && *envp)
// 	{
// 		while (envp[i] && !(ft_strnstr(envp[i], "PATH=", 5)))
// 			i++;
// 		if (!envp[i])
// 			return (NULL);
// 		path_var = ft_strtrim(envp[i], "PATH=");
// 		if (!path_var)
// 			return (NULL);
// 		env_paths = ft_split(path_var, ':');
// 		if (!env_paths)
// 			return (NULL);
// 		free(path_var);
// 		return (env_paths);
// 	}
// 	return (NULL);
// }

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
// 	int	i;

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
// 		printf("cmd: %s\n", list->cmd);
// 		printf("builtin: %d\n", list->builtin);
// 		printf("path: %s\n", list->path);
// 		i = 0;
// 		while (list->args[i])
// 		{
// 			printf("args[%d]: %s\n", i, list->args[i]);
// 			i++;
// 		}
// 		printf("args[%d]: %s\n", i, list->args[i]);
// 		// printf("args[1]: %s\n", list->args[1]);
// 		write(1, "\n", 1);
// 		list = list->next;
// 	}
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	t_lex 	*lex_lst;
// 	t_cmd	*cmd_lst;
// 	t_cmd	*start_lst;
// 	int		i = 1;
// 	char	**env_paths;
// 	char	input[] = "echo -n What | cat << eof | grep \"Hello World\" | ./script_dir/script.sh testarg | echo -nnnn lol | echo -nnn2 this | ls \"this is | a quote\"\0";

// 	(void)argc;
// 	(void)argv;
// 	lex_lst = lex(input);
// 	// ft_show_tab(lex_lst);

// 	env_paths = get_env_paths(envp);
// 	cmd_lst = parser(lex_lst, env_paths);
// 	start_lst = cmd_lst;
// 	ft_show_tab2(cmd_lst);

// 	while (env_paths[++i])
// 		free(env_paths[i]);
// 	free(env_paths);
// 	ft_cmd_lst_free(&start_lst);
// }