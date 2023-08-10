/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 17:20:07 by valmpani          #+#    #+#             */
/*   Updated: 2023/08/10 12:37:10 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef struct s_cmd
{
	char			*cmd;
	char			*path;
	int				opt; // make it an int
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

t_cmd	*parse(t_lex *lex_lst, char **env_paths);
int		analyze_token(t_lex **lex_lst, t_cmd *new_cmd, int *arg_num, char **env_paths);
int		set_here_doc_flag(t_lex **lex_lst, t_cmd *new_cmd);
int		set_redir_flags(t_lex **lex_lst, t_cmd *new_cmd);
int		allocate_args(t_lex *lex_lst, t_cmd *new_cmd);

int		analyze_word(t_lex **lex_lst, t_cmd *new_cmd, int *arg_num, char **env_paths);
int		analyze_cmd(t_lex **lex_lst, t_cmd *new_cmd, int *arg_num, char **env_paths);
int		check_word_type(t_lex *lex_lst, int hd_flag);
char	*get_path_name(t_cmd *new_cmd, char **env_paths);
int		get_cmd_name(t_lex **lex_lst, t_cmd *new_cmd);
int		check_for_builtin(t_lex **lex_lst, t_cmd *new_cmd);
int		check_word_type(t_lex *lex_lst, int in_flag);
void	check_for_path(t_lex **lex_lst, t_cmd *new_cmd);
int		analyze_opt(t_lex **lex_lst, t_cmd *new_cmd);

#endif