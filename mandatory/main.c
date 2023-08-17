/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:26:28 by valmpani          #+#    #+#             */
/*   Updated: 2023/08/17 15:11:19 by mamesser         ###   ########.fr       */
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

void	signals(void (*handler)(int))
{
	struct sigaction	sa;

	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	silence(void)
{
	struct termios	term;

	if (isatty(STDIN_FILENO))
	{
		tcgetattr(STDIN_FILENO, &term);
		term.c_lflag = term.c_lflag & ~ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}
	else if (isatty(STDOUT_FILENO))
	{
		tcgetattr(STDOUT_FILENO, &term);
		term.c_lflag = term.c_lflag & ~ECHOCTL;
		tcsetattr(STDOUT_FILENO, TCSANOW, &term);
	}
	else if (isatty(STDERR_FILENO))
	{
		tcgetattr(STDERR_FILENO, &term);
		term.c_lflag = term.c_lflag & ~ECHOCTL;
		tcsetattr(STDERR_FILENO, TCSANOW, &term);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char				*input[2];
	int					exit_code;
	t_lex				*lex_lst;
	t_env				*env_lst;
	t_cmd				*cmd_lst;
	

	if (argc > 1)
		return (1);
	(void)argv;
	exit_code = 0;
	cmd_lst = NULL;
	signals(handle_sigint);
	silence();
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
		else
		{
			cmd_lst = parser(lex_lst, env_lst);
			// ft_show_tab2(cmd_lst);
			if (!cmd_lst)
				exit_code = 1;
			else
				exit_code = execute(cmd_lst, env_lst, exit_code);
		}
		if (strcmp(input[1], "exit") == 0)
			exit_min(input[1], &lex_lst);
		add_history(input[1]);
		free(input[1]);
		ft_cmd_lst_free(&cmd_lst);
	}
}


// ft_show_tab2(cmd_lst);

void	ft_show_tab2(t_cmd *list)
{
	int	i;

	write(1, "\n", 1);
	while (list)
	{
		printf("cmd id: %d\n", list->cmd_id);
		if (list->file)
		{
			while (list->file)
			{
				printf("heredoc_delim: %s\n", list->file->delim);
				printf("file name: %s\n", list->file->name);
				printf("token: %c\n", list->file->token);
				list->file = list->file->next;
			}
		}
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