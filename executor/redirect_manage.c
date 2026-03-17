/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_manage.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aravelom <aravelom@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 07:29:04 by aravelom          #+#    #+#             */
/*   Updated: 2025/09/10 17:36:48 by aravelom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	error(char *filename, t_arg_child *arg)
{
	save_return_value(arg->exp, 1);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(filename, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
	return (1);
}

int	open_file(t_redir *in_out, t_arg_child *args)
{
	while (in_out)
	{
		if (*(in_out->redir) == '<' && !is_double_operator(in_out->redir))
			in_out->file_des = open(in_out->filename, O_RDONLY);
		if (*(in_out->redir) == '>')
		{
			if (is_double_operator(in_out->redir))
				in_out->file_des = open(in_out->filename,
						O_WRONLY | O_CREAT | O_APPEND, 0644);
			else
				in_out->file_des = open(in_out->filename,
						O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		if (in_out->file_des < 0)
		{
			if (!(in_out->redir[0] == '<' && is_double_operator(in_out->redir)))
				return (error(in_out->filename, args));
			else
				return (in_out->file_des);
		}
		in_out = in_out->next;
	}
	return (0);
}

int	out_in_file_cmd(t_redir *in_out, t_arg_child *args)
{
	if (open_file(in_out, args))
		return (1);
	while (in_out)
	{
		if (*(in_out->redir) == '<')
			close(in_out->file_des);
		if (*(in_out->redir) == '>')
		{
			dup2(in_out->file_des, STDOUT_FILENO);
			close(in_out->file_des);
		}
		in_out = in_out->next;
	}
	return (0);
}

void	out_in_file_cmds(t_cmd *cmd, t_arg_child *arg)
{
	t_redir	*in_out;

	in_out = cmd->in_out;
	if (open_file(in_out, arg))
	{
		free_all(arg);
		exit(EXIT_FAILURE);
	}
	while (in_out)
	{
		if (*(in_out->redir) == '<')
			dup2(in_out->file_des, STDIN_FILENO);
		if (*(in_out->redir) == '>')
			dup2(in_out->file_des, STDOUT_FILENO);
		close(in_out->file_des);
		in_out = in_out->next;
	}
	if (!cmd->args || !cmd->args[0])
	{
		free_all(arg);
		exit(EXIT_SUCCESS);
	}
}

void	redir_pipe(t_cmd *cmd, int *old_pipe, int *new_pipe)
{
	if (!old_pipe || !new_pipe)
		return ;
	if (cmd->num == 0)
		dup2(new_pipe[1], STDOUT_FILENO);
	else if (cmd->num != 0 && cmd->pipe == NULL)
		dup2(old_pipe[0], STDIN_FILENO);
	else
	{
		dup2(old_pipe[0], STDIN_FILENO);
		dup2(new_pipe[1], STDOUT_FILENO);
	}
	if (cmd->num != 0)
	{
		close(old_pipe[0]);
		close(old_pipe[1]);
	}
	close(new_pipe[0]);
	close(new_pipe[1]);
}
