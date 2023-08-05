/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmpani <valmpanis@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:26:28 by valmpani          #+#    #+#             */
/*   Updated: 2023/08/03 11:40:15 by valmpani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "../libft/libft.h"
#include "../readline/include/readline/history.h"
#include "../readline/include/readline/rlstdc.h"
#include "../readline/include/readline/readline.h"
#include "../includes/colors.h"

void	handle_sigquit(void)
{
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_sigint(int signum)
{
	if (signum == 3)
	{
		handle_sigquit();
		return ;
	}
	rl_replace_line("", 0);
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_redisplay();
}

void	exit_min(char *input)
{
	printf("Exiting minishell\n");
	if (input)
		free(input);
	exit(1);
}

char *get_git_head(void)
{
	char	buf[100];
	char	*temp;
	int		fd;
	int		i;
	size_t	bytes;

	fd = open(".git/HEAD", O_RDONLY);
	bytes = read(fd, buf, 100);
	i = 0;
	buf[bytes] = 0;
	while (buf[i])
		++i;
	while (buf[i] != '/')
		--i;
	i++;
	temp = ft_substr(buf, i, ft_strlen(buf) - (size_t)i);
	return (temp);
}

void get_repo(char **input)
{
	char	*temp;
	char 	*last_str;

	temp = get_git_head();
	last_str = ft_strjoin(*input, "\x1B[38;5;33mgit:(");
	free(*input);
	*input = last_str;
}

int	main(void)
{
	char				*input;
	struct sigaction	sa;

	sa.sa_handler = &handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	while (1)
	{
		input = ft_strjoin(BLUE, "minishell ");
		input = ft_strjoin(input, ESCAPE);
		if (access(".git/HEAD", O_RDONLY) == 0)
			get_repo(&input);
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
		input = readline(input);
		if (!input)
			exit_min(input);
		if (strcmp(input, "exit") == 0)
			exit_min(input);
		free(input);
	}
	return (0);
}
