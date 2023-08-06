/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 15:31:53 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/06 15:54:49 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum s_token
{
	TK_WORD;
	TK_SINGLE_QUOTE;
	TK_DOUBLE_QUOTE;
	TK_PIPE;
	TK_IN_R;
	TK_OUT_R;
	TK_APP_R;
	TK_HERE_DOC;
	TK_END_OF_LINE;
}			t_token;



#endif
