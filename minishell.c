/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aravelom <aravelom@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 19:31:03 by aravelom          #+#    #+#             */
/*   Updated: 2025/09/10 17:33:07 by aravelom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing/parsing.h"

int			g_signal = SIGQUIT;

static int	additional_parsing(t_arg_child *args)
{
	t_cmd	*cmd_tmp;
	t_redir	*in_out;

	cmd_tmp = NULL;
	in_out = NULL;
	if (!args || !(args->head))
		return (-1);
	cmd_tmp = args->head;
	while (cmd_tmp)
	{
		in_out = cmd_tmp->in_out;
		while (in_out)
		{
			if (*(in_out->redir) == '<' && is_double_operator(in_out->redir))
			{
				in_out->file_des = heredoc_fd(in_out, args);
				if (in_out->file_des < 0)
					return (-1);
			}
			in_out = in_out->next;
		}
		cmd_tmp = cmd_tmp->pipe;
	}
	return (0);
}

static int	cmd_exec(t_cmd *cmd, t_exp **exp, char *line)
{
	t_arg_child	args;

	args.exp = exp;
	args.head = cmd;
	args.fd = -1;
	args.pids = NULL;
	if (additional_parsing(&args) == 0)
		executor(cmd, exp, &line);
	free_cmd(&cmd);
	return (0);
}

static void	run_shell_loop(char *line, t_cmd *cmd, t_exp *exp, int *p)
{
	while (1)
	{
		ft_listen_signal();
		line = NULL;
		line = readline("minishell > ");
		act_sigint(save_return_value, &exp);
		if (line == NULL)
		{
			*p = ft_atoi(ft_lstchr("?", exp)->value);
			printf("exit\n");
			break ;
		}
		else
		{
			if (*line)
			{
				save_infile_history(MINISHELL_HISTORY, line);
				cmd = parsing(line, exp);
				cmd_exec(cmd, &exp, line);
				add_history(line);
			}
			free(line);
		}
	}
}

int	main(int c, char **v, char **env)
{
	int		status;
	char	*line;
	t_cmd	*cmd;
	t_exp	*exp;

	status = 0;
	exp = NULL;
	line = NULL;
	cmd = NULL;
	if (c > 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(v[0], 2);
		ft_putstr_fd(": too many arguments\n", 2);
		return (1);
	}
	ft_add_env(env, &exp);
	init_history(MINISHELL_HISTORY);
	run_shell_loop(line, cmd, exp, &status);
	ft_clear_env(&exp);
	rl_clear_history();
	return (status);
}
