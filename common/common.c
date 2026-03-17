/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aravelom <aravelom@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 10:42:20 by aravelom          #+#    #+#             */
/*   Updated: 2025/08/29 11:24:25 by aravelom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	save_return_value(t_exp **lst, int value)
{
	t_exp	*swap;
	char	*s;

	s = ft_itoa(value);
	if (!s)
		return ;
	swap = ft_lstchr("?", *lst);
	if (!swap)
	{
		swap = ft_newenv("?", s, 2);
		if (!swap)
			return (free(s));
		ft_addnew(lst, swap);
	}
	if (swap->value)
		free(swap->value);
	swap->value = s;
}

static char	*free_alloc(char *temp[3], char **split)
{
	free(temp[0]);
	free(temp[2]);
	ft_free_split(split);
	return (NULL);
}

char	*ft_cut_dollar(char *arg, t_exp *lst)
{
	int		i;
	char	*result;
	char	*temp[3];
	char	**split;
	t_exp	*swap;

	temp[2] = ft_strdup("");
	result = ft_strdup("");
	split = ft_split(arg, '$');
	i = -1;
	while (split && split[++i])
	{
		temp[0] = result;
		temp[1] = temp[2];
		swap = ft_lstchr(split[i], lst);
		if (swap && swap->value)
			temp[1] = swap->value;
		result = ft_strjoin(temp[0], temp[1]);
		if (!result)
			return (free_alloc(temp, split));
		free(temp[0]);
	}
	ft_free_split(split);
	free(temp[2]);
	return (result);
}

t_exp	*ft_lstchr(char *str, t_exp *lst)
{
	t_exp	*swap;

	if (!str)
		return (NULL);
	swap = lst;
	while (swap)
	{
		if (!ft_strncmp(swap->alias, str, ft_strlen(str) + 1))
			return (swap);
		swap = swap->next;
	}
	return (NULL);
}
