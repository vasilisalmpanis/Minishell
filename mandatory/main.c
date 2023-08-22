/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:26:28 by valmpani          #+#    #+#             */
/*   Updated: 2023/08/22 12:07:45 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_check_lex(t_lex *lst)
{
	while (lst)
	{
		if (lst->value[0] != '\0')
			return (0);
		lst = lst->next;
	}
	return (1);
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
		input[1] = readline(input[0]); //input[1] is allocated / gets freed in lexer split args
		free(input[0]);
		if (!input[1])
			exit_builtin(&env_lst, NULL);
		add_history(input[1]);
		if (input[1][0] == '\0')
			exit_code = 0;
		else
		{
			lex_lst = lex(input[1], exit_code); //lex_lst is allocated / gets freed in parser
			if (!lex_lst)
				exit_code = 1;
			else if (ft_check_lex(lex_lst))
				exit_code = 0;
			else
			{
				cmd_lst = parser(lex_lst, env_lst, exit_code);
				// ft_show_tab2(cmd_lst);
				if (!cmd_lst)
					exit_code = 1;
				else
					exit_code = execute(cmd_lst, env_lst, exit_code);
			}
			ft_cmd_lst_free(&cmd_lst);
		}
	}
}

// ft_show_tab2(cmd_lst);

void	ft_show_tab2(t_cmd *list)
{
	int	i;

	write(1, "\n", 1);
	while (list)
	{
		printf("pid: %d\n", list->pid);
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
