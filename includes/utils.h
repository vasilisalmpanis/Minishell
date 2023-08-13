/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:13:07 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/13 18:16:11 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "minishell.h"

t_cmd	*ft_new_cmd(int id, char **env_paths);
t_lex	*ft_new_tk(void *value, t_token token, int pos);
void	ft_lstadd_end(t_lex **lst, t_lex *new);
void	ft_cmd_lstadd_end(t_cmd **lst, t_cmd *new);
void	free_cmd_lex_env(t_cmd **cmd_lst, t_lex **lex_lst, char **env_paths);
void	ft_cmd_lst_free(t_cmd **lst);
void	ft_lst_free(t_lex **lst);

char	**split_args(char *input);
char	*ft_charjoin_mod(char *s1, char s2);
char	*ft_strjoin_mod(char *s1, char *s2);

void	handle_redirects(char **input, int j);
char	*add_space_pre_redir(char *input, int j);
char	*add_space_post_redir(char *input, int j);
int		calc_redir_wo_space(char *input);
int		calc_redir_wo_space2(char *input);
void	skip_quotes(char *input, int *i, char **new_input, int *j);
void	skip_quotes2(char *input, int *i);

#endif