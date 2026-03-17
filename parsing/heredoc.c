/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aravelom <aravelom@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 10:34:11 by aravelom          #+#    #+#             */
/*   Updated: 2025/09/10 10:07:24 by aravelom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	heredoc_warning(t_redir *redir, int *pipefd, t_arg_child *args)
{
	ft_putstr_fd("minishell: warning: here-document (wanted `", 2);
	ft_putstr_fd(redir->filename, 2);
	ft_putstr_fd("')\n", 2);
	free_all(args);
	close_fd(pipefd[1]);
	exit(EXIT_SUCCESS);
}

static int	write_in_a_fd(int *pipefd, t_redir *redir, t_arg_child *arg, int i)
{
	char	*line;
	char	*line_tmp;

	line = NULL;
	line_tmp = NULL;
	line = readline("heredoc> ");
	if (line == NULL)
		heredoc_warning(redir, pipefd, arg);
	if (ft_strcmp(redir->filename, line) == 0)
	{
		free(line);
		return (1);
	}
	if (i && *line)
		line_tmp = get_dollar_herdoc(line, *(arg->exp));
	else
		line_tmp = ft_strdup(line);
	write(pipefd[1], line_tmp, ft_strlen(line_tmp));
	write(pipefd[1], "\n", 1);
	if (*line)
		add_history(line);
	free(line_tmp);
	free(line);
	return (0);
}

static void	child_action(int *pipefd, t_redir *redir, t_arg_child *args)
{
	int		i;
	char	*str_tmp;

	i = 1;
	free_static(args, &(pipefd[1]));
	ft_def_sig_heredoc();
	close(pipefd[0]);
	if (ft_strchr(redir->filename, '\'') || ft_strchr(redir->filename, '"'))
		i = 0;
	str_tmp = clean_quotes(redir->filename);
	free(redir->filename);
	if (str_tmp == NULL)
		redir->filename = ft_calloc(1, 1);
	else
		redir->filename = str_tmp;
	while (1)
		if (write_in_a_fd(pipefd, redir, args, i))
			break ;
	rl_clear_history();
	close(pipefd[1]);
	free_all(args);
	exit(EXIT_SUCCESS);
}

int	heredoc_fd(t_redir *redir, t_arg_child *args)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	if (pipe(pipefd) == -1)
		return (-1);
	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid == 0)
		child_action(pipefd, redir, args);
	else
	{
		signal(SIGINT, SIG_IGN);
		close(pipefd[1]);
		waitpid(pid, &status, 0);
		status = ft_child_sig_return(status);
		if (status != 0)
		{
			close(pipefd[0]);
			save_return_value(args->exp, status);
			return (-status);
		}
	}
	return (pipefd[0]);
}
