/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:26:28 by valmpani          #+#    #+#             */
/*   Updated: 2023/08/14 12:05:17 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_min(char *input, t_lex **lst)
{
	printf("Exiting minishell\n");
	ft_lst_free(lst);
	if (input)
		free(input);
	exit(1);
}

int	main(void)
{
	char				*input;
	char				*temp;
	struct sigaction	sa;
	t_lex				*lst;

	sa.sa_handler = &handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	while (1)
	{
		temp = prompt();
		input = readline(temp);
		free(temp);
		if (!input)
			exit_min(input);
		// get env vars
		// create a copy of input to pass to lex
		lst = lex(input);
		// ft_show_tab(lst);
		// parse input
		// allocate memory for fds
		// create pipes --> creates list of cmds
		// execute commands --> return process ids
		if (strcmp(input, "exit") == 0)
			exit_min(input, &lst);
		add_history(input);
		//close fds
		//wait for children and handle exit status
		free(input);
		ft_lst_free(&lst); // probably only need to free the cmd lst and not lex as lex is freed when parsing
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