/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aravelom <aravelom@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 09:45:26 by aravelom          #+#    #+#             */
/*   Updated: 2025/09/10 16:12:19 by aravelom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static pid_t	*pids_alloc(t_cmd *cmd)
{
	pid_t	*pids;
	ssize_t	nb;

	if (!cmd)
		return (NULL);
	pids = NULL;
	nb = 0;
	while (cmd)
	{
		nb++;
		cmd = cmd->pipe;
	}
	pids = (pid_t *)malloc(sizeof(pid_t) * nb);
	if (!pids)
		return (NULL);
	return (pids);
}

static void	wait_cmd_end(t_exp **exp, pid_t *pids, int num)
{
	int	status;
	int	x;

	x = 0;
	while (x < num)
		waitpid(pids[x++], &status, 0);
	free(pids);
	status = ft_child_sig_return(status);
	save_return_value(exp, status);
}

static int	exec_cmds(t_cmd *cmd, t_exp **exp)
{
	int			num;
	pid_t		*pids;
	t_pipes		pipes;
	t_arg_child	arg;

	num = 0;
	pids = pids_alloc(cmd);
	if (pids == NULL)
		return (-1);
	arg.pids = pids;
	arg.head = cmd;
	arg.exp = exp;
	arg.fd = -1;
	while (cmd)
	{
		if (cmd->pipe != NULL)
			pipe(pipes.new_pipe);
		pids[num] = process_manage(cmd, &pipes, &arg);
		if (pids[num] < 0)
			break ;
		cmd = cmd->pipe;
		num++;
	}
	wait_cmd_end(exp, pids, num);
	return (0);
}

static int	exec_builtins(t_cmd *cmd, char **line, t_arg_child *args)
{
	int	ret;

	if (!(args->exp))
		return (1);
	cmd->env = ft_env_to_tab(*(args->exp));
	cmd->cmd_path = NULL;
	if (is_builins_cmd(cmd->args[0]) == 1)
		args->fd = dup(STDOUT_FILENO);
	ret = out_in_file_cmd(cmd->in_out, args);
	if (ret != 0)
	{
		close_fd(args->fd);
		save_return_value(args->exp, ret);
		ft_free_split(cmd->env);
		return (ret);
	}
	ret = in_builtins(cmd, args->exp, line, NULL);
	if (args->fd >= 0)
		dup2(args->fd, STDOUT_FILENO);
	close_fd(args->fd);
	save_return_value(args->exp, ret);
	ft_free_split(cmd->env);
	return (ret);
}

int	executor(t_cmd *cmd, t_exp **exp, char **line)
{
	int			ret;
	t_arg_child	args;

	signal(SIGINT, SIG_IGN);
	if (!cmd)
		return (-1);
	args.head = cmd;
	args.pids = NULL;
	args.exp = exp;
	args.fd = -1;
	if ((!cmd->args || !cmd->args[0]) && cmd->in_out)
	{
		open_file(cmd->in_out, &args);
		return (0);
	}
	if (!cmd->args || !cmd->args[0])
		return (-1);
	if (!cmd->pipe && is_builins_cmd(cmd->args[0]))
		ret = exec_builtins(cmd, line, &args);
	else
		ret = exec_cmds(cmd, exp);
	return (ret);
}
