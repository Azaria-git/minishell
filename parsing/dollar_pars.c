/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_pars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aravelom <aravelom@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:01:36 by aravelom          #+#    #+#             */
/*   Updated: 2025/09/10 17:35:41 by aravelom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	result_on_double_quote(char *line, t_exp *exp, t_list **lst)
{
	int		i;
	char	*temp;

	i = 0;
	ft_lstnew_addback(lst, ft_strdup("\""));
	while (line[i] && line[i] != '"')
	{
		if (line[i + 1] && line[i] == '$'
			&& (line[i + 1] == '$' || line[i + 1] == '?'
				|| line[i + 1] == '_' || ft_isalnum(line[i + 1])))
		{
			i += creat_word('$', line + i + 1, "?\" \'$", &temp) + 1;
			exp_to_lst(temp, exp, lst);
		}
		else
			i += add_word_lst('\0', line + i, "\"$", lst);
	}
	ft_lstnew_addback(lst, ft_strdup("\""));
	return (i);
}

static char	*ft_lst_tostring(t_list *lst)
{
	int		i;
	char	**temp;
	char	*line;

	temp = ft_calloc(ft_lstsize(lst) + 1, sizeof(char *));
	if (!temp)
		return (NULL);
	i = 0;
	while (lst)
	{
		temp[i] = ft_strdup(lst->content);
		i++;
		lst = lst->next;
	}
	line = ft_join(temp, 0);
	ft_free_split(temp);
	return (line);
}

static char	*result_param(char **tokens, t_exp *exp, int y)
{
	char	*result;

	result = NULL;
	result = get_dollar(tokens[y], exp);
	if (result && result[0] == '\0' && y > 0
		&& is_operator_char(tokens[y - 1][0]))
		return (result);
	if (!result)
		return (NULL);
	if (*result == '\0')
		ft_free_null((void **)&result);
	return (result);
}

char	*get_dollar(char *line, t_exp *exp)
{
	t_list	*lst;
	char	*temp;

	lst = NULL;
	while (*line != 0)
	{
		if (*line == '"' && *(line + 1))
			line += result_on_double_quote(line + 1, exp, &lst) + 2;
		else if (*line == '\'' && *(line + 1))
			line += add_word_lst('\'', line, "\'", &lst);
		else if (line[1] && *line == '$' && (line[1] == '$' || line[1] == '_'
				|| line[1] == '?' || ft_isalnum(line[1]) || line[1] == '\''
				|| line[1] == '\"'))
		{
			line += creat_word('$', line + 1, "?\" \'$", &temp) + 1;
			exp_to_lst(temp, exp, &lst);
		}
		else
			line += add_word_lst('\0', line, "$\"\'", &lst);
	}
	temp = ft_lst_tostring(lst);
	ft_lstclear(&lst, free);
	return (temp);
}

char	**dollar_parameter(char **tokens, t_exp *exp)
{
	ssize_t	y;
	ssize_t	len;
	char	**new;

	if (!tokens)
		return (NULL);
	len = ft_strlen_strtab(tokens, NULL);
	new = (char **)ft_calloc(len + 1, sizeof(char *));
	len = 0;
	y = -1;
	while (new && tokens[++y])
	{
		if (ft_strchr(tokens[y], '$') && !(y > 0 && tokens[y - 1][0] == '<'
			&& is_double_operator(tokens[y - 1])))
		{
			new[len] = result_param(tokens, exp, y);
			if (!new[len])
				len--;
		}
		else
			new[len] = ft_strdup(tokens[y]);
		len++;
	}
	ft_free_split(tokens);
	return (new);
}
