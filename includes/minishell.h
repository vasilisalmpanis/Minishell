/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 14:26:53 by valmpani          #+#    #+#             */
/*   Updated: 2023/08/06 16:34:53 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <termios.h>
# include <string.h>
# include <signal.h>
# include "lexer.h"
# include "utils.h"
# include "builtins.h"
# include "parser.h"
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
void	get_repo(char **input, char *head);
char	*get_git_head(void);
char	*prompt(char **cur_dir);
char	*current_dir(void);

//UTILS

//BUILTINS
int		pwd(void);
int		echo(t_cmd cmd);
int		cd_dir(t_cmd cmd);
int		env(t_env *lst, t_cmd cmd);
t_env	*lst_env_node(char *key, char *value);
void	ft_env_addback(t_env **lst, t_env *new);
void	ft_env_free(t_env **lst);
void	ft_env_remove(t_env **begin_list, char *key);
t_env	*create_env(char **en);
void	export_print(t_env *lst);
int		export(t_env **lst, t_cmd *cmd);

#endif
