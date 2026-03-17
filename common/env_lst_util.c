/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aravelom <aravelom@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 11:48:03 by aravelom          #+#    #+#             */
/*   Updated: 2025/09/11 07:51:39 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

t_exp	*ft_newenv(char *alias, char *value, int status)
{
	t_exp	*res;

	res = malloc(sizeof(t_exp));
	if (!res)
		return (NULL);
	res->alias = ft_strdup(alias);
	if (!res->alias)
	{
		free(res);
		return (NULL);
	}
	res->value = ft_strdup(value);
	res->status = status;
	res->next = NULL;
	return (res);
}

t_exp	*ft_lastenv(t_exp *lst)
{
	t_exp	*swap;

	swap = lst;
	if (!swap)
		return (lst);
	while (swap->next)
		swap = swap->next;
	return (swap);
}

void	ft_addnew(t_exp **lst, t_exp *nw)
{
	t_exp	*swap;

	swap = *lst;
	if (swap && !swap->next && nw)
		swap->next = nw;
	else if (swap && nw)
	{
		swap = ft_lastenv(swap);
		swap->next = nw;
	}
	else if (!swap && nw)
		*lst = nw;
	else
		return ;
}

void	ft_clear_env(t_exp **lst)
{
	t_exp	*swap1;
	t_exp	*swap2;

	swap1 = *lst;
	if (!swap1)
		return ;
	while (swap1)
	{
		swap2 = swap1->next;
		if (swap1->alias)
			free(swap1->alias);
		if (swap1->value)
			free(swap1->value);
		free(swap1);
		swap1 = swap2;
	}
	*lst = NULL;
}
