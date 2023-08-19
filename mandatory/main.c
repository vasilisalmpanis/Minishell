/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:26:28 by valmpani          #+#    #+#             */
/*   Updated: 2023/08/19 12:14:04 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_min(char *input, t_lex **lst, int exit_code)
{
	(void)lst;
	if (input)
		free(input);
	exit(exit_code);
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
	exit_code = 0;
	cmd_lst = NULL;
	signals(handle_sigint);
	silence();
	env_lst = create_env(envp, argv); //env_lst is allocated
	if (!env_lst)
		return (1);
	while (1)
	{
		signals(handle_sigint);
		input[0] = prompt();
		input[1] = readline(input[0]); //input[1] is allocated?
		free(input[0]);
		if (!input[1])
			exit_min(input[1], &lex_lst, exit_code);
		input[0] = ft_strdup(input[1]); //input[0] is allocated / gets freed in lexer split_args
		if (!input[0])
			return (1);
		lex_lst = lex(input[0], exit_code); //lex_lst is allocated / gets freed in parser
		if (!lex_lst)
			exit_code = 1;
		else
		{
			cmd_lst = parser(lex_lst, env_lst, exit_code);
			if (!cmd_lst)
				exit_code = 1;
			else
				exit_code = execute(cmd_lst, env_lst, exit_code);
		}
		if (strcmp(input[1], "exit") == 0)
			exit_min(input[1], &lex_lst, exit_code);
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
