/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aravelom <aravelom@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 09:58:57 by aravelom          #+#    #+#             */
/*   Updated: 2025/09/08 14:35:45 by aravelom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H
# include "../Libft/libft.h"
# include <readline/readline.h>
# include <unistd.h>
# include <signal.h>
# include "../struct.h"
# include "../common/common.h"

void	ft_clear_ctr_c(int sig);
void	ft_react_herdoc(int sig);
void	ft_def_sig_heredoc(void);
void	ft_listen_signal(void);
void	ft_def_sig_child(void);
int		ft_child_sig_return(int status);
void	act_sigint(void (save_return_value)(t_exp **, int), t_exp **exp);

#endif
