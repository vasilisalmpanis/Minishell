/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valmpani <valmpani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 13:57:53 by valmpani          #+#    #+#             */
/*   Updated: 2023/08/11 13:57:53 by valmpani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

// Define color escape codes with invisible markers
# define MINI "minishell: "
# define ID ": not a valid identifier\n"
# define CD1 "cd: error retrieving current directory: getcwd:"
# define CD2 " cannot access parent directories: No such file or directory\n"
# define NO_CD "cd: no such file or directory:"

#endif
