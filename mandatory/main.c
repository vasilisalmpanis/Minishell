/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmpani <valmpanis@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:26:28 by valmpani          #+#    #+#             */
/*   Updated: 2023/08/06 13:33:37 by valmpani         ###   ########.fr       */
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

	sa.sa_handler = &handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	while (1)
	{
		temp = ft_strdup(GREEN"→" BLUE"  minishell "ESCAPE);
		if (access(".git/HEAD", O_RDONLY) == 0)
			get_repo(&temp);
		input = readline(temp);
		free(temp);
		if (!input)
			exit_min(input);
		if (strcmp(input, "exit") == 0)
			exit_min(input);
		add_history(input);
		free(input);
	}
	return (0);
}
