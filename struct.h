/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aravelom <aravelom@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 10:38:45 by aravelom          #+#    #+#             */
/*   Updated: 2025/08/29 15:04:11 by aravelom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include <aio.h>
# include <stdlib.h>

typedef struct s_exp
{
	char			*alias;
	char			*value;
	int				status;
	struct s_exp	*next;
}					t_exp;

typedef struct s_redir
{
	char			*redir;
	char			*filename;
	int				file_des;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	size_t			num;
	char			**args;
	char			**cmd_path;
	t_redir			*in_out;
	char			**env;
	struct s_cmd	*pipe;
}					t_cmd;

typedef struct s_arg_child
{
	t_cmd			*head;
	pid_t			*pids;
	t_exp			**exp;
	int				fd;
}					t_arg_child;

#endif