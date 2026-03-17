/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splite_tokens_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aravelom <aravelom@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 20:23:42 by aravelom          #+#    #+#             */
/*   Updated: 2025/08/04 11:18:29 by aravelom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static ssize_t	scape_string(char *line, ssize_t *count)
{
	ssize_t	i;
	char	current;

	i = 0;
	if (line == NULL)
		return (0);
	current = line[i];
	i++;
	while (line[i] && !(line[i] == current && line[i - 1] != '\\'))
		i++;
	if (line[i] == current)
		i++;
	*count = *count + 1;
	return (i);
}

ssize_t	count_rest(char *line)
{
	ssize_t	ret;
	ssize_t	count;

	count = 0;
	ret = 0;
	while (line[ret])
	{
		if (is_operator_char(line[ret]) || is_shell_whitespace(line[ret]))
			return (ret);
		if (line[ret] == '\'' || line[ret] == '"')
			ret = ret + scape_string(line + ret, &count);
		else
			ret++;
	}
	return (ret);
}

ssize_t	count_size(char *line)
{
	ssize_t	count;

	count = 0;
	while (*line)
	{
		while (*line && is_shell_whitespace(*line))
			line++;
		if (!(*line))
			break ;
		else if (is_operator_char(*line))
		{
			line = line + 1 + is_double_operator(line);
			count++;
		}
		else
		{
			line = line + count_rest(line);
			count++;
		}
	}
	return (count);
}

char	*remove_token_from(char **tokens, ssize_t y)
{
	char	*token;

	if (tokens[y] == NULL)
		return (NULL);
	token = ft_strdup(tokens[y]);
	while (tokens[y])
	{
		free(tokens[y]);
		tokens[y] = ft_strdup(tokens[y + 1]);
		y++;
	}
	return (token);
}
