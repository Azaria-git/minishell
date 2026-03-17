/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   removing_quot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aravelom <aravelom@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:02:48 by aravelom          #+#    #+#             */
/*   Updated: 2025/08/25 14:55:12 by aravelom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	effective_len(char **original)
{
	int	y;

	y = 0;
	while (original[y])
		y++;
	return (y);
}

static int	size_needed(char *str)
{
	int		result;
	char	quot;

	result = 0;
	while (*str)
	{
		if (*str != '\'' && *str != '"')
		{
			result++;
			str++;
		}
		else
		{
			quot = *str;
			str++;
			while (*str && *str != quot)
			{
				result++;
				str++;
			}
			if (*str == quot)
				str++;
		}
	}
	return (result);
}

static char	*copy_without_quotes(char *original, int size)
{
	char	*copy;
	char	quot;
	int		x;

	if (size == 0)
		return ((char *)ft_calloc(1, 1));
	copy = (char *)ft_calloc(size + 1, 1);
	x = 0;
	if (!copy)
		return (NULL);
	while (*original)
	{
		if (*original != '\'' && *original != '"')
			copy[x++] = *(original++);
		else
		{
			quot = *original;
			original++;
			while (*original && *original != quot)
				copy[x++] = *(original++);
			if (*original == quot)
				original++;
		}
	}
	return (copy);
}

char	*clean_quotes(char *original)
{
	int	size;

	if (!original)
		return (NULL);
	size = size_needed(original);
	if (size == 0)
		return (NULL);
	return (copy_without_quotes(original, size));
}

char	**clean_quotes_tab(char **original)
{
	char	**str_clean;
	int		len;
	int		size;
	int		y;

	str_clean = NULL;
	if (!original)
		return (NULL);
	len = effective_len(original);
	if (len == 0)
		return (NULL);
	str_clean = (char **) malloc(sizeof(char *) * (len + 1));
	if (!str_clean)
		return (NULL);
	str_clean[len] = NULL;
	len = 0;
	y = 0;
	while (original[len])
	{
		size = size_needed(original[len]);
		str_clean[y++] = copy_without_quotes(original[len], size);
		len++;
	}
	return (str_clean);
}
