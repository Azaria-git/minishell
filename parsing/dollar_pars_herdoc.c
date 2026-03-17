/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_pars_herdoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aravelom <aravelom@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:01:36 by aravelom          #+#    #+#             */
/*   Updated: 2025/09/09 10:51:50 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	manager_case_dollar_creat(char *line, char **res)
{
	if (line[0] == '$')
	{
		*res = ft_strdup("$$");
		return (1);
	}
	*res = ft_strdup("");
	return (0);
}

int	manager_dollar_creat(char *line, char **res, char *stop)
{
	int			i;
	static char	buf[2] = {0};

	if (line && (line[0] == '$' || line[0] == '\"' || line[0] == '\''))
		return (manager_case_dollar_creat(line, res));
	if (line && ft_isdigit(line[0]))
	{
		buf[0] = line[0];
		*res = ft_strdup(buf);
		return (1);
	}
	i = 0;
	while (line[i] && !ft_strchr(stop, line[i]) && (line[i] == '_'
			|| ft_isalnum(line[i])))
		i++;
	if (i == 0 && (line[0] == '?' || (line[0] == '$')))
		i = 1;
	*res = ft_substr(line, 0, i);
	return (i);
}

static void	exp_to_lst_herdoc(char *str, t_exp *exp, t_list **lst)
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
		ft_lstnew_addback(lst, ft_strdup(temp->value));
	else
		ft_lstnew_addback(lst, ft_strdup(""));
	free(str);
}

static char	*ft_lst_tostring_herdoc(t_list *lst)
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

char	*get_dollar_herdoc(char *line, t_exp *exp)
{
	t_list	*lst;
	char	*temp;

	lst = NULL;
	while (*line != 0)
	{
		if (*(line + 1) && *line == '$' && (*(line + 1) == '$'
				|| *(line + 1) == '?' || *(line + 1) == '?'
				|| ft_isalnum(*(line + 1))))
		{
			line += creat_word('$', line + 1, "?\" \'$", &temp) + 1;
			exp_to_lst_herdoc(temp, exp, &lst);
		}
		else
			line += add_word_lst('\0', line, "$", &lst);
	}
	temp = ft_lst_tostring_herdoc(lst);
	ft_lstclear(&lst, free);
	return (temp);
}
