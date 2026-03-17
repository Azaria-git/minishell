/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aravelom <aravelom@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 20:05:43 by aravelom          #+#    #+#             */
/*   Updated: 2025/09/10 13:47:21 by aravelom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_shell_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

int	is_operator_char(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

int	is_double_operator(char *line)
{
	if (!(line + 1))
		return (0);
	if ((*line == '>' && *(line + 1) == '>') || (*line == '<' && *(line
				+ 1) == '<') || (*line == '|' && *(line + 1) == '|'))
		return (1);
	return (0);
}

char	**duplicate_array(char **original)
{
	char	**array_dup;
	ssize_t	len;

	len = 0;
	array_dup = NULL;
	if (original == NULL)
		return (NULL);
	while (original[len])
		len++;
	array_dup = (char **)malloc(sizeof(char *) * (len + 1));
	if (array_dup == NULL)
		return (NULL);
	array_dup[len] = NULL;
	len = 0;
	while (original[len])
	{
		array_dup[len] = ft_strdup(original[len]);
		len++;
	}
	return (array_dup);
}

int	ft_lstnew_addback(t_list **lst, char *str)
{
	t_list	*elm;

	elm = ft_lstnew(str);
	ft_lstadd_back(lst, elm);
	return (1);
}
