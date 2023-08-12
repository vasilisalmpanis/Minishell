/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 17:20:07 by valmpani          #+#    #+#             */
/*   Updated: 2023/08/12 16:02:19 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

// typedef struct s_env
// {
// 	char			*key;
// 	char			*value;
// 	struct s_env	*next;
// }		t_env;

typedef struct s_cmd
{
	char			*cmd;
	char			*path;
	int				opt;
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
	int				env_flag;
	char			*delim;
	char			*file;
	struct s_cmd	*next;
}				t_cmd;

t_cmd	*parser(t_lex *lex_lst, t_env *env_lst);
int		parse_tokens(t_lex *lex_lst, t_cmd **cmd_lst, char **env_paths);
int		allocate_args(t_lex *lex_lst, t_cmd *new_cmd);
int		analyze_token(t_lex **lex_lst, t_cmd *new_cmd, int *arg_num, char **env_p);
char	**extract_paths(t_env **env_lst);

int		set_here_doc_flag(t_lex **lex_lst, t_cmd *new_cmd);
int		set_redir_flags(t_lex **lex_lst, t_cmd *new_cmd);

int		analyze_word(t_lex **lex_lst, t_cmd *new_cmd, int *arg_num, char **env_p);
int		check_word_type(t_lex *lex_lst, int in_flag);
int		analyze_cmd(t_lex **lex_lst, t_cmd *new_cmd, int *arg_num, char **env_p);
int		analyze_opt(t_lex **lex_lst, t_cmd *new_cmd);

int		check_for_builtin(t_lex **lex_lst, t_cmd *new_cmd);
void	check_for_path(t_lex **lex_lst, t_cmd *new_cmd);
int		get_cmd_name(t_lex **lex_lst, t_cmd *new_cmd);
char	*get_path_name(t_cmd *new_cmd, char **env_paths);


#endif