/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmpani <valmpanis@student.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:25:21 by valmpani          #+#    #+#             */
/*   Updated: 2023/08/06 19:02:59 by valmpani         ###   ########.fr       */
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
