/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_manage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aravelom <aravelom@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 07:24:49 by aravelom          #+#    #+#             */
/*   Updated: 2025/09/10 16:12:40 by aravelom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static void	put_error(const char *arg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd((char *)arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("command not found\n", 2);
}

static void	child_action(t_cmd *cmd, t_pipes *pipes, t_arg_child *args)
{
	ssize_t	y;
	int		bult_ret;

	y = 0;
	ft_def_sig_child();
	cmd->env = ft_env_to_tab(*(args->exp));
	if (cmd->args != NULL)
		cmd->cmd_path = cmd_path(cmd->env, cmd->args[0], args, 0);
	if (cmd->num == 0 && cmd->pipe == NULL)
		redir_pipe(cmd, NULL, NULL);
	else
		redir_pipe(cmd, pipes->old_pipe, pipes->new_pipe);
	out_in_file_cmds(cmd, args);
	bult_ret = in_builtins(cmd, args->exp, NULL, args);
	if (bult_ret != -1)
	{
		free_all(args);
		exit(bult_ret);
	}
	while (cmd->cmd_path && cmd->cmd_path[y])
		execve(cmd->cmd_path[y++], cmd->args, cmd->env);
	if (cmd->cmd_path != NULL)
		put_error(cmd->args[0]);
	free_all(args);
	exit(127);
}

static int	parent_action(t_cmd *cmd, int *old_pipe, int *new_pipe)
{
	if (cmd->num == 0 && cmd->pipe == NULL)
		return (0);
	if (!old_pipe || !new_pipe)
		return (-1);
	if (cmd->num != 0)
	{
		close(old_pipe[0]);
		close(old_pipe[1]);
	}
	if (cmd->pipe != NULL)
	{
		old_pipe[0] = new_pipe[0];
		old_pipe[1] = new_pipe[1];
	}
	return (1);
}

pid_t	process_manage(t_cmd *cmd, t_pipes *pipes, t_arg_child *args)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		perror("minishell: ");
	else if (pid == 0)
		child_action(cmd, pipes, args);
	else
	{
		parent_action(cmd, pipes->old_pipe, pipes->new_pipe);
	}
	return (pid);
}
