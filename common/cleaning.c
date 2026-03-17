/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aravelom <aravelom@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 11:05:10 by aravelom          #+#    #+#             */
/*   Updated: 2025/09/09 10:34:10 by aravelom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	free_static(t_arg_child *arg, int *fd)
{
	static t_arg_child	*stat_arg = NULL;
	static int			*fd_stat = NULL;

	if (arg && fd)
	{
		stat_arg = arg;
		fd_stat = fd;
	}
	else if (stat_arg && fd_stat)
	{
		close(*fd_stat);
		free_all(stat_arg);
		stat_arg = NULL;
		fd_stat = NULL;
	}
}

void	close_fd(int fd)
{
	if (fd >= 0)
		close(fd);
}

void	free_redir(t_redir **redir)
{
	t_redir	*tmp;

	while (*redir)
	{
		tmp = (*redir)->next;
		ft_free_null((void **)&(*redir)->filename);
		free((*redir)->redir);
		close_fd((*redir)->file_des);
		ft_free_null((void **)redir);
		*redir = tmp;
	}
}

void	free_cmd(t_cmd **cmd_pars)
{
	t_cmd	*tmp;

	if (cmd_pars == NULL || (*cmd_pars) == NULL)
		return ;
	while (*cmd_pars)
	{
		tmp = (*cmd_pars)->pipe;
		if ((*cmd_pars)->args)
			ft_free_split((*cmd_pars)->args);
		ft_free_split((*cmd_pars)->cmd_path);
		free_redir(&(*cmd_pars)->in_out);
		free(*cmd_pars);
		*cmd_pars = tmp;
	}
}

void	free_all(t_arg_child *args)
{
	t_cmd	*cmd;
	t_cmd	*tmp;

	if (!args)
		return ;
	cmd = args->head;
	if (args->exp)
		ft_clear_env(args->exp);
	if (args->pids)
		free(args->pids);
	close_fd(args->fd);
	while (cmd)
	{
		tmp = cmd->pipe;
		if (cmd->args)
			ft_free_split(cmd->args);
		if (cmd->cmd_path)
			ft_free_split(cmd->cmd_path);
		if (cmd->in_out)
			free_redir(&(cmd->in_out));
		if (cmd->env)
			ft_free_split(cmd->env);
		free(cmd);
		cmd = tmp;
	}
}
