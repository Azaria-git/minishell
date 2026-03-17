/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aravelom <aravelom@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:19:55 by marrandr          #+#    #+#             */
/*   Updated: 2025/09/12 11:11:12 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "../common/common.h"
# include <asm-generic/errno-base.h>
# include <limits.h>

int		ft_assign_join(char *str, t_exp **lst, int status, char *swap);
int		count_char_diff(char *s, char *a, int i, int nb);
int		write_error(int er, char *info, char *cmd);
t_exp	*ft_lstchr(char *str, t_exp *lst);
int		syntax_error(char *str);
int		ft_assign(char *str, t_exp **lst, int status);
int		ft_assign_export(char *str, t_exp **lst);
int		ft_export(t_exp *lst);
int		ft_env(char	**arg, t_exp *lst);
void	ft_add_env(char **env, t_exp **lst);
int		ft_count_arg(char **split);
int		in_builtins(t_cmd *arg, t_exp **lst, char **line, t_arg_child *args);
int		ft_ischar(const char *str, char c);
int		ft_pwd(char **args);
int		ft_cd(char **args, t_exp **lst, char *str);
int		ft_unset(char **arg, t_exp *lst);
char	**ft_strcut(char const *s, char c, char **res);
void	ft_free_tab(char **tab);
int		ft_echo(char **str, int check);
char	*ft_cut_dollar(char *arg, t_exp *lst);
int		error_export(char *str, char *cmd);
char	**ft_env_to_tab(t_exp *lst);
char	*ft_strtrimall(char const *s1, char const *set);
int		error_command(char *cmd);
int		ft_exit(t_cmd **cmd, t_exp **exp, char **line, t_arg_child *args);
void	save_pid_value(t_exp **lst);
int		ft_free_pointer(void *arg);
int		ft_free_array_pointer(char **type);
int		is_builins_cmd(char *cmd);
int		ft_assign_export_local(char *alias, char *value, t_exp **lst);

#endif
