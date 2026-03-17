/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aravelom <aravelom@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 11:05:29 by aravelom          #+#    #+#             */
/*   Updated: 2025/08/04 11:17:48 by aravelom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	count_pipes(char *line)
{
	int	count;
	int	tmp;

	count = 1;
	if (*line == '|')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (-1);
	}
	while (*line)
	{
		tmp = 1;
		if (*line == '\'' || *line == '"')
			tmp = escape_quote(line);
		else if (*line == '|')
		{
			tmp = escape_pipes(line);
			count++;
		}
		if (tmp < 0)
			return (-1);
		else
			line = line + tmp;
	}
	return (count);
}

static char	*new_pipes_part(char *line, int *x)
{
	int		len;
	char	*ret;

	len = 0;
	ret = NULL;
	while (line[len])
	{
		if (line[len] == '\'' || line[len] == '"')
			len += escape_quote(line + len);
		else if (line[len] == '|')
			break ;
		else
			len++;
	}
	ret = (char *)ft_calloc(len + 1, 1);
	if (ret == NULL)
		return (NULL);
	if (!ft_memcpy(ret, line, len))
		ft_free_null((void **)&ret);
	if (line[len] == '|')
		len++;
	*x = *x + len;
	return (ret);
}

static char	**fill_pipes(char *line, char **pipes)
{
	int		x;
	int		y;
	char	*new;

	x = 0;
	y = 0;
	while (line[x])
	{
		new = NULL;
		new = new_pipes_part(line + x, &x);
		if (new == NULL)
		{
			ft_free_split(pipes);
			return (NULL);
		}
		pipes[y] = new;
		y++;
	}
	return (pipes);
}

char	**split_pipes(char *line)
{
	int		size;
	char	**pipes;

	if (!line)
		return (NULL);
	pipes = NULL;
	size = count_pipes(line);
	if (size < 0)
		return (NULL);
	pipes = (char **)malloc(sizeof(char *) * (size + 1));
	if (pipes == NULL)
		return (NULL);
	if (!fill_pipes(line, pipes))
		return (NULL);
	pipes[size] = NULL;
	return (pipes);
}
