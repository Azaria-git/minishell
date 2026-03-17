/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splite_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aravelom <aravelom@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:17:07 by aravelom          #+#    #+#             */
/*   Updated: 2025/08/04 10:51:29 by aravelom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*new_operator_token(char *line, ssize_t *x)
{
	ssize_t	i;
	char	*new_token;

	new_token = NULL;
	i = 1 + is_double_operator(line + *x);
	new_token = (char *)malloc(i + 1);
	if (new_token == NULL)
		return (NULL);
	new_token[i] = '\0';
	if (!ft_memcpy(new_token, line + *x, i))
	{
		free(new_token);
		return (NULL);
	}
	*x = *x + i;
	return (new_token);
}

static char	*new_word_token(char *line, ssize_t *x)
{
	ssize_t	i;
	char	*new_token;

	i = 0;
	new_token = NULL;
	if (*(line + *x) == '\0')
		return (NULL);
	line = line + *x;
	i = count_rest(line);
	new_token = (char *)malloc(i + 1);
	if (new_token == NULL)
		return (NULL);
	new_token[i] = '\0';
	if (!ft_memcpy(new_token, line, i))
	{
		free(new_token);
		return (NULL);
	}
	*x = *x + i;
	return (new_token);
}

static char	**fill_tockens(char *line, char **tokens)
{
	ssize_t	x;
	ssize_t	i;
	char	*new_token;

	x = 0;
	i = 0;
	while (line[x])
	{
		new_token = NULL;
		while (line[x] && is_shell_whitespace(line[x]))
			x++;
		if (!(line[x]))
			break ;
		else if (is_operator_char(line[x]))
			new_token = new_operator_token(line, &x);
		else
			new_token = new_word_token(line, &x);
		tokens[i] = new_token;
		if (new_token == NULL)
			return (free_tokens(tokens));
		i++;
	}
	return (tokens);
}

char	**split_tokens(char *line)
{
	ssize_t	size;
	char	**tockens;

	tockens = NULL;
	size = count_size(line);
	tockens = (char **)malloc(sizeof(char *) * (size + 1));
	if (tockens == NULL)
		return (NULL);
	if (!fill_tockens(line, tockens))
		return (NULL);
	tockens[size] = NULL;
	return (tockens);
}
