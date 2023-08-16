/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:26:28 by valmpani          #+#    #+#             */
/*   Updated: 2023/08/16 12:47:08 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_min(char *input, t_lex **lst)
{
	printf("Exiting minishell\n");
	(void)lst;
	// ft_lst_free(lst);
	if (input)
		free(input);
	exit(1);
}

int	main(int argc, char **argv, char **envp)
{
	char				*input[2];
	int					exit_code;
	struct sigaction	sa;
	t_lex				*lex_lst;
	t_env				*env_lst;
	t_cmd				*cmd_lst;
	

	if (argc > 1)
		return (1);
	(void)argv;
	exit_code = 0;
	sa.sa_handler = &handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	env_lst = create_env(envp);
	if (!env_lst)
		return (1);
	while (1)
	{
		input[0] = prompt();
		input[1] = readline(input[0]);
		free(input[0]);
		if (!input[1])
			exit_min(input[1], &lex_lst);
		input[0] = ft_strdup(input[1]);
		if (!input[0])
			return (1);
		lex_lst = lex(input[0], exit_code); // maybe check for null or in parser
		if (!lex_lst)
			exit_code = 1;
		cmd_lst = parser(lex_lst, env_lst);
		// ft_show_tab2(cmd_lst);
		execute(cmd_lst, env_lst);
		if (strcmp(input[1], "exit") == 0)
			exit_min(input[1], &lex_lst);
		add_history(input[1]);
		free(input[1]);
		ft_cmd_lst_free(&cmd_lst);
	}
}

// ft_show_tab(lst);

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
		printf("app_flag: %d\n", list->app_flag);
		printf("infile: %s\n", list->in_file);
		printf("outfile: %s\n", list->out_file);
		printf("appfile: %s\n", list->app_file);
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
		printf("args[%d]: %s\n", i, list->args[i]);
		// printf("args[1]: %s\n", list->args[1]);
		write(1, "\n", 1);
		list = list->next;
	}
}



/* ----------------------TEST MAIM---------------------- */
//void	parse(char *input, t_env **lst)
//{
//	t_cmd cmd1;
//	t_env *node;
//	char **temp;
//	char **var;
//
//	cmd1.args = NULL;
//	if (strcmp(input, "env") == 0)
//		env(*lst, cmd1);
//	else if (ft_strncmp(input, "export", 6) == 0)
//	{
//		int i = 0;
//		temp = split_args(input);
//		cmd1.args = ft_calloc(2, 1);
//		while (temp[i])
//			++i;
//		if (i == 1)
//		{
//			cmd1.args = NULL;
//			export(lst, &cmd1);
//			return;
//		}
//		cmd1.args[0] = temp[1];
//		var = ft_split(cmd1.args[0], '=');
//		export(lst, &cmd1);
//	}
//	else if (ft_strncmp(input, "unset", 5) == 0)
//	{
//		temp = ft_split(input,  ' ');
//		ft_env_remove(lst, temp[1]);
//		return ;
//	}
//	if (strcmp(input, "..") == 0)
//		if (chdir("..") != 0)
//			perror("cd");
//	if (strcmp(input, "cd") == 0)
//		chdir("test");
//	if (!input)
//		exit_min(input, NULL);
//	if (strcmp(input, "exit") == 0)
//	{
//		exit_min(input, NULL);
//	}
//}
//
//int	main(int argc, char **argv, char **en)
//{
//	char				*input;
//	char				*temp;
//	t_cmd 				cmd1;
//	t_env				*lst;
//
//	argc++;
//	argv++;
//	cmd1.args = NULL;
//	lst = create_env(en);
//	while (1)
//	{
//		temp = prompt();
//		input = readline(temp);
//		free(temp);
//		parse(input, &lst);
//		add_history(input);
//		free(input);
//	}
//}