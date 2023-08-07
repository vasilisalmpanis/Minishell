/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmpani <valmpani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 17:20:07 by valmpani          #+#    #+#             */
/*   Updated: 2023/08/07 17:20:37 by valmpani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_cmd
{
	char			*cmd;
	char			*path;
	char			*opts;
	char			**args;
	int				cmd_id;
	int				builtin;
	int				path_known;
	int				is_script;
	int				in;
	int				out;
	int				fd[2];
	pid_t			pid;
	int				hd_flag;
	char			**env;
	struct s_cmd	*next;
}				t_cmd;

#endif