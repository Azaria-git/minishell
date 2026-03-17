/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_pars_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aravelom <aravelom@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 09:54:44 by aravelom          #+#    #+#             */
/*   Updated: 2025/09/04 12:48:22 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	count_word(char const *str, char sep)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != sep && (i == 0 || str[i - 1] == sep))
			count++;
		i++;
	}
	return (count);
}

int	creat_word(char source, char *line, char *stop, char **res)
{
	int	i;

	i = 0;
	if (line && source == '$')
		return (manager_dollar_creat(line, res, stop));
	else if (line && source == '\0')
	{
		i = 0;
		if (line[0] == '$')
			i = 1;
		while (line[i] && !ft_strchr(stop, line[i]))
			i++;
		if (i == 0 && (line[0] == '?' || (line[0] == '$')))
			i = 1;
		*res = ft_substr(line, 0, i);
	}
	else if (line && source == '\'')
	{
		i = 1;
		while (line[i] && !ft_strchr(stop, line[i]))
			i++;
		*res = ft_substr(line, 0, ++i);
	}
	return (i);
}

int	add_word_lst(char source, char *line, char *stop, t_list **lst)
{
	int		i;

	i = 0;
	if (line && source == '\0')
	{
		i = 0;
		if (line[0] == '$')
			i = 1;
		while (line[i] && !ft_strchr(stop, line[i]))
			i++;
		if (i == 0 && (line[0] == '?' || (line[0] == '$')))
			i = 1;
		ft_lstnew_addback(lst, ft_substr(line, 0, i));
	}
	else if (line && source == '\'')
	{
		i = 1;
		while (line[i] && !ft_strchr(stop, line[i]))
			i++;
		ft_lstnew_addback(lst, ft_substr(line, 0, ++i));
	}
	return (i);
}

static void	manager_value_exp(char *value, t_list **lst)
{
	char	**split;
	int		i;

	if (!count_word(value, ' '))
		ft_lstnew_addback(lst, ft_strdup("\"\""));
	else
	{
		split = ft_split(value, ' ');
		if (!split)
			return ;
		i = 0;
		while (split && split[i])
		{
			if (i)
				ft_lstnew_addback(lst, ft_strdup(" "));
			ft_lstnew_addback(lst, ft_strdup("\""));
			ft_lstnew_addback(lst, split[i++]);
			ft_lstnew_addback(lst, ft_strdup("\""));
		}
		free (split);
	}
}

void	exp_to_lst(char *str, t_exp *exp, t_list **lst)
{
	t_exp	*temp;

	if (!str)
		return ;
	if (!*str || !ft_strncmp(str, "$", 2))
	{
		free (str);
		return ;
	}
	temp = ft_lstchr(str, exp);
	if (temp && temp->value && (*temp->value))
		manager_value_exp(temp->value, lst);
	else
		ft_lstnew_addback(lst, ft_strdup(""));
	free(str);
}
