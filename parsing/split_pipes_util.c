/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aravelom <aravelom@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:24:23 by aravelom          #+#    #+#             */
/*   Updated: 2025/09/10 16:28:32 by aravelom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	escape_pipes(char *line)
{
	int	i;
	int	x;

	i = 1;
	x = 1;
	if (line[i] == '\0' || line[i] == '|')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (-1);
	}
	while (line[x] && is_shell_whitespace(line[x]))
		x++;
	if (line[x] == '\0' || line[x] == '|')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (-1);
	}
	return (i);
}

int	escape_quote(char *line)
{
	char	quote;
	int		i;

	i = 0;
	quote = line[i];
	i++;
	while (line[i] && line[i] != quote)
		i++;
	if (line[i] == quote)
		i++;
	else
	{
		ft_putstr_fd("minishell: quote error\n", 2);
		return (-1);
	}
	return (i);
}
