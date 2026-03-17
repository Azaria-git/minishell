/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_tools1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aravelom <aravelom@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 09:40:55 by marrandr          #+#    #+#             */
/*   Updated: 2025/09/12 07:24:41 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_assign_export_local(char *alias, char *value, t_exp **lst)
{
	t_exp	*this;

	this = ft_lstchr(alias, *lst);
	if (this)
	{
		this->status = 1;
		if (value)
		{
			if (this->value)
				free (this->value);
			this->value = ft_strdup(value);
		}
		return (0);
	}
	this = ft_newenv(alias, value, 1);
	if (!this)
		return (1);
	ft_addnew(lst, this);
	return (0);
}

static int	ft_free_all(char **res, int i)
{
	if (res[i] != NULL)
		return (0);
	while (i >= 0)
		free(res[i--]);
	free(res);
	return (1);
}

static size_t	ft_count_len(char const *str, char sep, unsigned int index)
{
	size_t	count;

	count = 0;
	while (str[index] && str[index] != sep)
	{
		count++;
		index++;
	}
	return (count);
}

char	**ft_strcut(char const *s, char c, char **res)
{
	int	i;

	if (s && ft_ischar(s, c) < 2)
		res = ft_split(s, c);
	else if (s)
	{
		res = (char **)malloc(3 * sizeof(char *));
		if (res == NULL)
			return (NULL);
		i = ft_count_len(s, c, 0);
		res[0] = ft_substr(s, 0, i);
		if (ft_free_all(res, 0))
			return (NULL);
		res[1] = ft_substr(s, ++i, -1);
		if (ft_free_all(res, 1))
			return (NULL);
		res[2] = NULL;
	}
	return (res);
}

int	ft_free_array_pointer(char **type)
{
	int	i;

	i = 0;
	if (!type)
		return (1);
	while (type[i])
	{
		if (type[i])
			free(type[i]);
		i++;
	}
	free(type);
	return (1);
}
