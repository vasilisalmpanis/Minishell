/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmpani <valmpanis@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:25:21 by valmpani          #+#    #+#             */
/*   Updated: 2023/08/17 10:36:17 by valmpani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_sigquit(void)
{
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_sigint(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		putchar('\n');
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_sigint_child(int signum)
{
	putchar('\n');
//	rl_replace_line("", 0);
}

void	handle_sigquit_child(int signum)
{
	putchar('\n');
	ft_putstr_fd("Quit: ", STDERR_FILENO);
	ft_putnbr_fd(signum, STDERR_FILENO);
	putchar('\n');
	rl_replace_line("", 0);
	exit(130);
}

void	signals(void (*handler)(int))
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
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
