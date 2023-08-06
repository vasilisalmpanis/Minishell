/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:26:53 by valmpani          #+#    #+#             */
/*   Updated: 2023/08/06 15:31:47 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include "lexer.h"
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

//UTILS
char	**split_args(t_data object, int i);

#endif
