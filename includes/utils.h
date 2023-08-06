/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:13:07 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/06 16:31:52 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lex	*ft_new_tk(void *value, t_token token);
void	ft_lstadd_end(t_lex **lst, t_lex *new);
void	ft_lst_free(t_lex **lst);

char	**split_args(char *input);
