/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmpani <valmpani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 11:59:44 by valmpani          #+#    #+#             */
/*   Updated: 2023/08/10 11:59:44 by valmpani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * Function:  export
 * --------------------
 * Prints the env list if cmd has no arguments
 * Checks for syntactic errors in the key to be added
 * Adds the key to the end of the list and thr value accordingly if it exists
 * @lst	Reference to the env list
 * @cmd Reference to the command given by lexer
 */
int	export(t_env **lst, t_cmd *cmd)
{
	if (!cmd->args)
		export_print(*lst);
	return (0);
	// functions to parse keys for syntax errors
	// functions to add key, value to list
}


/*
 * Function:  export_print
 * --------------------
 * Prints the env list with declare -x before and if node has no value
 * it doesn't print the ='${lst.value}'
 * @lst	Reference to the env list
 */
void	export_print(t_env *lst)
{
	t_env	*exp;

	exp = lst;
	while (exp)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(exp->key, 1);
		if (exp->value[0] != '\0')
		{
			ft_putstr_fd("='", 1);
			ft_putstr_fd(exp->value, 1);
			ft_putstr_fd("'\n", 1);
		}
		else
			ft_putstr_fd("\n", 1);
		exp = exp->next;
	}
}