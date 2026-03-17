/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_def_proc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aravelom <aravelom@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 10:37:16 by marrandr          #+#    #+#             */
/*   Updated: 2025/09/11 11:48:39 by aravelom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	ft_def_sig_heredoc(void)
{
	signal(SIGINT, ft_react_herdoc);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_def_sig_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	ft_listen_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_clear_ctr_c);
}
