/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:13:07 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/10 12:51:47 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "minishell.h"

t_cmd	*ft_new_cmd(int id);
t_lex	*ft_new_tk(void *value, t_token token, int pos);
void	ft_lstadd_end(t_lex **lst, t_lex *new);
void	ft_cmd_lstadd_end(t_cmd **lst, t_cmd *new);
void	free_cmd_and_lex(t_cmd **cmd_lst, t_lex **lex_lst);
void	ft_cmd_lst_free(t_cmd **lst);
void	ft_lst_free(t_lex **lst);

char	**split_args(char *input);
int		ft_isspace(char c);
char	*ft_charjoin_mod(char *s1, char s2);
char	*ft_strjoin_mod(char *s1, char *s2);

#endif