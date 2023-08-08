/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 17:20:07 by valmpani          #+#    #+#             */
/*   Updated: 2023/08/08 18:09:20 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef struct s_cmd
{
	char			*cmd;
	char			*path;
	char			*opts;
	char			**args;
	int				builtin;
	int				path_known;
	int				is_sh_script;
	// int				fd[2];
	pid_t			pid;
	int				cmd_id;
	int				in_flag;
	int				out_flag;
	int				app_flag;
	int				hd_flag;
	char			*delim;
	char			*file;
	char			**env;
	struct s_cmd	*next;
}				t_cmd;

t_cmd	*parse(t_lex *lex_lst);
int		analyze_token(t_lex **lex_lst, t_cmd *new_cmd, int *pos, int *arg_num);
int		set_here_doc_flag(t_lex **lex_lst, t_cmd *new_cmd);
int		set_redir_flags(t_lex **lex_lst, t_cmd *new_cmd);

int		analyze_word(t_lex **lex_lst, t_cmd *new_cmd, int pos, int *arg_num);
int		check_word_type(int	hd_flag, int pos);

#endif