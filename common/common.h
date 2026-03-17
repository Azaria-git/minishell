/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aravelom <aravelom@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 10:42:36 by aravelom          #+#    #+#             */
/*   Updated: 2025/09/08 15:39:41 by aravelom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H
# include "../Libft/libft.h"
# include "../signals/signals.h"
# include "../struct.h"
# include <errno.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

char	*ft_cut_dollar(char *arg, t_exp *lst);
t_exp	*ft_lstchr(char *str, t_exp *lst);
void	save_return_value(t_exp **lst, int value);
t_exp	*ft_newenv(char *alias, char *value, int status);
t_exp	*ft_lastenv(t_exp *lst);
void	ft_addnew(t_exp **lst, t_exp *nw);
void	ft_clear_env(t_exp **lst);
void	free_redir(t_redir **redir);
void	free_cmd(t_cmd **cmd_pars);
void	free_all(t_arg_child *args);
void	free_static(t_arg_child *arg, int *fd);
void	close_fd(int fd);

#endif