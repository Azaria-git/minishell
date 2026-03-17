/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_redirects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aravelom <aravelom@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 09:45:15 by aravelom          #+#    #+#             */
/*   Updated: 2025/09/10 17:37:21 by aravelom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	filename_param(t_redir *in_out)
{
	char	*tmp;

	tmp = NULL;
	if (*(in_out->redir) == '<' && is_double_operator(in_out->redir))
		return ;
	if (*(in_out->filename))
	{
		tmp = clean_quotes(in_out->filename);
		free(in_out->filename);
		in_out->filename = tmp;
	}
}

static void	add_redir(t_redir **head, t_redir *new_redir)
{
	t_redir	*tmp;

	if (head == NULL || new_redir == NULL)
		return ;
	tmp = *head;
	if (tmp == NULL)
	{
		new_redir->next = NULL;
		*head = new_redir;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	new_redir->next = NULL;
	tmp->next = new_redir;
}

static int	has_redirection(char *line)
{
	char	tmp;

	if (line == NULL)
		return (0);
	while (*line)
	{
		tmp = *line;
		if (tmp == '"' || tmp == '\'')
		{
			line++;
			while (*line && *line != tmp)
				line++;
			if (*line)
				line++;
		}
		else if (tmp == '>' || tmp == '<')
			return (1);
		else
			line++;
	}
	return (0);
}

static t_redir	*take_file_redirects(char **tokens, char *str, t_redir *redir)
{
	t_redir	*tmp;
	ssize_t	y;

	y = 0;
	while (tokens[y])
	{
		if (has_redirection(tokens[y]))
		{
			tmp = (t_redir *)malloc(sizeof(t_redir));
			if (tmp == NULL)
				return (redir);
			tmp->redir = remove_token_from(tokens, y);
			tmp->file_des = -1;
			str = remove_token_from(tokens, y);
			tmp->filename = ft_strdup(str);
			ft_free_null((void **)&str);
			add_redir(&redir, tmp);
		}
		else
			y++;
	}
	return (redir);
}

int	in_out_file(char **tokens, t_cmd **new, t_exp **exp)
{
	t_redir	*tmp;

	if (new == NULL || *new == NULL)
		return (-1);
	(*new)->in_out = take_file_redirects(tokens, NULL, NULL);
	tmp = (*new)->in_out;
	while (tmp)
	{
		if (tmp->filename == NULL || is_operator_char(tmp->filename[0]))
		{
			ft_putstr_fd("minishell: parse error near `\\n'\n", 2);
			free_redir(&(*new)->in_out);
			(*new)->args = NULL;
			(*new)->pipe = NULL;
			(*new)->cmd_path = NULL;
			(*new)->env = NULL;
			save_return_value(exp, 2);
			return (-1);
		}
		filename_param(tmp);
		tmp = tmp->next;
	}
	return (0);
}
