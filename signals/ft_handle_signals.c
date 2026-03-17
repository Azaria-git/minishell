/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_signals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aravelom <aravelom@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 11:45:11 by marrandr          #+#    #+#             */
/*   Updated: 2025/09/08 15:41:03 by aravelom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

extern int	g_signal;

void	ft_clear_ctr_c(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = SIGINT;
		write (STDIN_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_react_herdoc(int sig)
{
	if (sig == SIGINT)
	{
		free_static(NULL, NULL);
		exit (130);
	}
}

int	ft_child_sig_return(int status)
{
	int	ret_child;

	if (WIFSIGNALED(status))
	{
		ret_child = WTERMSIG(status);
		if (ret_child == SIGINT)
			return (write (STDIN_FILENO, "\n", 1), 130);
		else if (ret_child == SIGQUIT)
		{
			write (2, "Quit (core dumped)\n", 19);
			return (131);
		}
		else
			return (ret_child + 128);
	}
	else if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (0);
}

void	act_sigint(void (save_return_value)(t_exp **, int), t_exp **exp)
{
	if (g_signal == SIGINT)
	{
		g_signal = SIGQUIT;
		save_return_value(exp, 130);
	}
}
