/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:26:28 by valmpani          #+#    #+#             */
/*   Updated: 2023/08/07 12:09:33 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_min(char *input)
{
	printf("Exiting minishell\n");
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
	char				**str;

	sa.sa_handler = &handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	str = malloc(2 * sizeof(char *));
	str[0] = getcwd(NULL, 0);
	str[1] = get_git_head();
	while (1)
	{
		temp = prompt(str);
		input = readline(temp);
		lst = lex(input);
		free(temp);
		if (!input)
			exit_min(input);
		if (strcmp(input, "exit") == 0)
			exit_min(input);
		add_history(input);
		free(input);
		ft_lst_free(&lst);
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
//		if (!var[1])
//			node = lst_env_node(var[0], var[1]);
//		else
//		{
//			var[1] = ft_strtrim(var[1], "\"");
//			node = lst_env_node(var[0], var[1]);
//		}
//		ft_env_addback(&(*lst),node);
//		cmd1.args = NULL;
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
//		exit_min(input);
//	if (strcmp(input, "exit") == 0)
//	{
//		exit_min(input);
//	}
//}
//
//int	main(int argc, char **argv, char **en)
//{
//	char				*input;
//	char				*temp;
//	char				**str;
//	t_cmd 				cmd1;
//	t_env				*lst;
//
//	argc++;
//	argv++;
//	cmd1.args = NULL;
//	lst = create_env(en);
//	str = (char **)ft_calloc((2), sizeof(char *));
//	str[0] = getcwd(NULL, 0);
//	str[1] = get_git_head();
//	while (1)
//	{
//		temp = prompt(str);
//		input = readline(temp);
//		free(temp);
//		parse(input, &lst);
//		add_history(input);
//		free(input);
//	}
//}