/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aravelom <aravelom@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:14:26 by aravelom          #+#    #+#             */
/*   Updated: 2025/09/09 09:36:08 by aravelom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_cmd	*new_cmd(char *line, t_exp **exp)
{
	t_cmd	*new;
	char	**tokens;

	new = NULL;
	tokens = NULL;
	tokens = dollar_parameter(split_tokens(line), *exp);
	if (tokens == NULL)
		return (NULL);
	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (new != NULL)
	{
		if (in_out_file(tokens, &new, exp) != 0)
		{
			free_tokens(tokens);
			ft_free_null((void *)&new);
			return (NULL);
		}
		new->args = clean_quotes_tab(tokens);
		new->pipe = NULL;
		new->cmd_path = NULL;
		new->env = NULL;
	}
	free_tokens(tokens);
	return (new);
}

static t_cmd	**add_cmd(t_cmd **head, t_cmd *new, size_t num)
{
	t_cmd	*tmp;

	if (head == NULL || new == NULL)
		return (NULL);
	if (*head == NULL)
	{
		new->pipe = NULL;
		new->num = num;
		*head = new;
		return (head);
	}
	tmp = *head;
	while (tmp->pipe)
		tmp = tmp->pipe;
	new->pipe = NULL;
	new->num = num;
	tmp->pipe = new;
	return (head);
}

t_cmd	*parsing(char *line, t_exp *exp)
{
	char	**lines;
	t_cmd	*cmd_pars;
	size_t	y;

	y = 0;
	lines = NULL;
	cmd_pars = NULL;
	lines = split_pipes(line);
	if (lines == NULL)
	{
		save_return_value(&exp, 2);
		return (NULL);
	}
	while (lines[y])
	{
		if (!add_cmd(&cmd_pars, new_cmd(lines[y], &exp), y))
		{
			ft_free_split(lines);
			free_cmd(&cmd_pars);
			return (NULL);
		}
		y++;
	}
	ft_free_split(lines);
	return (cmd_pars);
}
