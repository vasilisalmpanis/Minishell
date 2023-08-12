/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmpani <valmpani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:02:47 by valmpani          #+#    #+#             */
/*   Updated: 2023/08/08 11:02:51 by valmpani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "minishell.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}		t_env;

// pwd
int		pwd(void);

// echo
int		echo(t_cmd cmd);

// cd
int		cd_dir(t_cmd cmd);

// env_list
int		env(t_env *lst, t_cmd cmd);
t_env	*lst_env_node(char *key, char *value);
void	ft_env_addback(t_env **lst, t_env *new);
void	ft_env_free(t_env **lst);
void	ft_env_remove(t_env **begin_list, char *key);
t_env	*create_env(char **en);

// export
void	export_print(t_env *lst);
int		export(t_env **lst, t_cmd *cmd);
int		export_args(t_env **lst, t_cmd *cmd);
int		check_arg(char *arg, char *name);
void	ft_split_key_val(char *arg, char **key, char **value);

// unset


#endif
