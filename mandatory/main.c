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

//int	main(void)
//{
//	char				*input;
//	char				*temp;
//	struct sigaction	sa;
//	t_lex				*lst;
//	char				**str;
//
//	sa.sa_handler = &handle_sigint;
//	sigemptyset(&sa.sa_mask);
//	sa.sa_flags = 0;
//	sigaction(SIGINT, &sa, NULL);
//	sigaction(SIGQUIT, &sa, NULL);
//	str = malloc(2 * sizeof(char *));
//	str[0] = getcwd(NULL, 0);
//	str[1] = get_git_head();
//	while (1)
//	{
//		temp = prompt(str);
//		input = readline(temp);
//		lst = lex(input);
//		free(temp);
//		if (!input)
//			exit_min(input);
//		if (strcmp(input, "exit") == 0)
//			exit_min(input);
//		add_history(input);
//		free(input);
//		ft_lst_free(&lst);
//	}
//}

int	main(void)
{
	char				*input;
	char				*temp;
	char				**str;

	str = (char **)ft_calloc((2), sizeof(char *));
	str[0] = getcwd(NULL, 0);
	str[1] = get_git_head();
	while (1)
	{
		temp = prompt(str);
		input = readline(temp);
		free(temp);
		if (strcmp(input, "..") == 0)
			if (chdir("..") != 0)
				perror("cd");
		if (strcmp(input, "cd") == 0)
			chdir("test");
		if (!input)
			exit_min(input);
		if (strcmp(input, "exit") == 0)
		{
			free(str[0]);
			free(str[1]);
			free(str);
			exit_min(input);
		}
		add_history(input);
		free(input);
	}
}