/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamesser <mamesser@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 18:23:58 by mamesser          #+#    #+#             */
/*   Updated: 2023/08/19 09:29:03 by mamesser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*parser(t_lex *lex_lst, t_env *env_lst, int exit_code)
{
	t_cmd	*cmd_lst;
	char	**env_paths;

	cmd_lst = NULL;
	env_paths = extract_paths(&env_lst); // env_paths get allocated // NULL is valid return; e.g. in case path has been unset
	if (parse_tokens(lex_lst, &cmd_lst, env_paths, exit_code))
		return (free_cmd_lex_env(&cmd_lst, &lex_lst, env_paths), NULL);
	ft_lst_free(&lex_lst);
	if (env_paths)
		ft_free(env_paths);
	return (cmd_lst);
}

char	**extract_paths(t_env **env_lst)
{
	char	*path_values;
	char	**env_paths;

	path_values = NULL;
	while (*env_lst)
	{
		if (!(ft_strncmp((*env_lst)->key, "PATH", ft_strlen((*env_lst)->key))))
		{
			path_values = strdup((*env_lst)->value);
			break ;
		}
		free(path_values);
		path_values = NULL;
		env_lst = &((*env_lst)->next);
	}
	env_paths = ft_split(path_values, ':');
	if (!env_paths)
		return (NULL);
	free(path_values);
	return (env_paths);
}

int	parse_tokens(t_lex *lex_lst, t_cmd **cmd_lst, char **env_paths, int ex_co)
{
	t_cmd	*new_cmd;
	int		arg_num;
	int		id;

	id = 0;
	while (lex_lst)
	{
		new_cmd = ft_new_cmd(id++, env_paths, ex_co);
		if (!new_cmd)
			return (1);
		arg_num = 0;
		if (allocate_args(lex_lst, new_cmd))
			return (free(new_cmd), 1);
		while (lex_lst && lex_lst->token != TK_PIPE)
		{
			if (analyze_token(&lex_lst, new_cmd, &arg_num, env_paths))
				return (free(new_cmd), 1);
			lex_lst = lex_lst->next;
		}
		(new_cmd->args)[arg_num] = NULL;
		ft_cmd_lstadd_end(cmd_lst, new_cmd);
		if (lex_lst)
			lex_lst = lex_lst->next;
	}
	return (0);
}

int	allocate_args(t_lex *lex_lst, t_cmd *new_cmd)
{
	int		arg_num;
	t_lex	**start_lst;

	start_lst = &lex_lst;
	arg_num = 0;
	while (*start_lst && (*start_lst)->token != TK_PIPE)
	{
		if ((*start_lst)->token == TK_WORD)
			arg_num++;
		else if ((*start_lst)->token == TK_IN_R
			|| (*start_lst)->token == TK_OUT_R
			|| (*start_lst)->token == TK_APP_R
			|| (*start_lst)->token == TK_HERE_DOC)
		{
			arg_num -= 1;
		}
		start_lst = &(*start_lst)->next;
	}
	if (arg_num >= 0)
	{
		new_cmd->args = malloc((arg_num + 1) * sizeof(char *)); // probably allocated too much memory in case of builtin
		if (!new_cmd->args)
			return (1);
	}
	return (0);
}

int	analyze_token(t_lex **lex_lst, t_cmd *new_cmd, int *arg_num, char **env_p)
{
	if ((*lex_lst)->token == TK_WORD)
	{
		if (analyze_word(lex_lst, new_cmd, arg_num, env_p))
			return (1);
	}
	else if ((*lex_lst)->token == TK_HERE_DOC)
	{
		if (set_here_doc_flag(lex_lst, new_cmd))
			return (1);
	}
	else if ((*lex_lst)->token == TK_APP_R
		|| (*lex_lst)->token == TK_IN_R
		|| (*lex_lst)->token == TK_OUT_R)
	{
		if (set_redir_flags(lex_lst, new_cmd))
			return (1);
	}
	return (0);
}
