/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aravelom <aravelom@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:45:42 by aravelom          #+#    #+#             */
/*   Updated: 2025/09/10 13:22:44 by aravelom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "../builtins/builtins.h"
# include "../common/common.h"
# include "../parsing/parsing.h"
# include "../struct.h"
# include <sys/stat.h>
# include <sys/wait.h>

typedef struct s_pipes
{
	int	old_pipe[2];
	int	new_pipe[2];
}		t_pipes;

char	**cmd_path(char **env, char *cmd, t_arg_child *arg, int is_built);
int		out_in_file_cmd(t_redir *in_out, t_arg_child *args);
void	out_in_file_cmds(t_cmd *cmd, t_arg_child *args);
void	redir_pipe(t_cmd *cmd, int *old_pipe, int *new_pipe);
pid_t	process_manage(t_cmd *cmd, t_pipes *pipes, t_arg_child *args);
int		executor(t_cmd *cmd, t_exp **exp, char **line);
int		open_file(t_redir *in_out, t_arg_child *args);

#endif