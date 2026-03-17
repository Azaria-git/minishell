/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aravelom <aravelom@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 19:37:33 by aravelom          #+#    #+#             */
/*   Updated: 2025/09/10 10:05:09 by aravelom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "../common/common.h"
# include "../struct.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/types.h>
# include <sys/wait.h>

int		creat_word(char source, char *line, char *stop, char **res);
char	**dollar_parameter(char **tokens, t_exp *exp);
int		escape_quote(char *line);
int		escape_pipes(char *line);
char	**split_pipes(char *line);
ssize_t	count_rest(char *line);
ssize_t	count_size(char *line);
char	*remove_token_from(char **tokens, ssize_t y);
char	**split_tokens(char *line);
int		is_shell_whitespace(char c);
int		is_operator_char(char c);
int		is_double_operator(char *line);
char	**duplicate_array(char **original);
char	*new_token_from_q(char *line, ssize_t *x);
char	**free_tokens(char **tokens);
t_cmd	*parsing(char *line, t_exp *exp);
char	**clean_quotes_tab(char **original);
char	*clean_quotes(char *original);
char	*get_dollar(char *line, t_exp *exp);
int		in_out_file(char **tokens, t_cmd **new, t_exp **exp);
int		manager_dollar_creat(char *line, char **res, char *stop);
int		ft_lstnew_addback(t_list **lst, char *str);
void	exp_to_lst(char *str, t_exp *exp, t_list **lst);
int		add_word_lst(char source, char *line, char *stop, t_list **lst);
char	*get_dollar_herdoc(char *line, t_exp *exp);
int		heredoc_fd(t_redir *redir, t_arg_child *args);

#endif
