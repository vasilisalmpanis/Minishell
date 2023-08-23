/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:26:28 by valmpani          #+#    #+#             */
/*   Updated: 2023/08/23 15:42:39 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		g_signal_num;

void	start_env(int *exit_code, int argc)
{
	if (argc > 1)
		exit (1);
	*exit_code = 0;
	silence();
}

void	set_ex_code(int *exit_code)
{
	signals(handle_sigint);
	if (g_signal_num == 258)
	{
		*exit_code = g_signal_num;
		g_signal_num = 0;
	}
	else if (g_signal_num > 0)
	{
		*exit_code = 128 + g_signal_num;
		g_signal_num = 0;
	}
	else if (g_signal_num == -1)
	{
		*exit_code = 1;
		g_signal_num = 0;
	}
}

char	*ft_get_prompt(t_env **env_lst)
{
	char	*temp;
	char	*result;

	temp = prompt();
	result = readline(temp);
	free(temp);
	if (!result)
		exit_builtin(env_lst, NULL);
	add_history(result);
	return (result);
}

void	run_minishell(t_env **env_lst, int *exit_code, char *input)
{
	t_lex	*lex_lst;
	t_cmd	*cmd_lst;

	lex_lst = NULL;
	cmd_lst = NULL;
	lex_lst = lex(input, *exit_code);
	if (!lex_lst)
		*exit_code = 1;
	else if (ft_check_lex(lex_lst))
		*exit_code = 0;
	else
	{
		cmd_lst = parser(lex_lst, *env_lst, *exit_code);
		if (!cmd_lst)
			*exit_code = 1;
		else
		{
			add_start_lst(cmd_lst);
			*exit_code = execute(cmd_lst, env_lst, *exit_code);
		}
	}
	ft_cmd_lst_free(&cmd_lst);
}

int	main(int argc, char **argv, char **envp)
{
	char				*input;
	int					exit_code;
	t_env				*env_lst;

	start_env(&exit_code, argc);
	env_lst = create_env(envp, argv);
	if (!env_lst)
		return (1);
	while (1)
	{
		set_ex_code(&exit_code);
		input = ft_get_prompt(&env_lst);
		if (input[0] == '\0')
			exit_code = 0;
		else
			run_minishell(&env_lst, &exit_code, input);
	}
	return (0);
}

// ft_show_tab2(cmd_lst);
// void	ft_show_tab2(t_cmd *list)
// {
// 	int	i;

// 	write(1, "\n", 1);
// 	while (list)
// 	{
// 		printf("pid: %d\n", list->pid);
// 		printf("cmd id: %d\n", list->cmd_id);
// 		if (list->file)
// 		{
// 			while (list->file)
// 			{
// 				printf("heredoc_delim: %s\n", list->file->delim);
// 				printf("file name: %s\n", list->file->name);
// 				printf("token: %c\n", list->file->token);
// 				list->file = list->file->next;
// 			}
// 		}
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