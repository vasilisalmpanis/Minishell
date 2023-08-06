/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmpani <valmpani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:26:53 by valmpani          #+#    #+#             */
/*   Updated: 2023/08/06 14:26:58 by valmpani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include "../libft/libft.h"
# include "../includes/colors.h"
# define READLINE_LIBRARY
# include "../readline/include/history.h"
# include "../readline/include/readline.h"
# include "../readline/include/rlstdc.h"

//SIGNALS
void	handle_sigquit(void);
void	handle_sigint(int signum);

//PROMPT
void	get_repo(char **input);
char	*get_git_head(void);

#endif
