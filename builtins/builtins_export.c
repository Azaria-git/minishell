/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aravelom <aravelom@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:16:22 by marrandr          #+#    #+#             */
/*   Updated: 2025/09/12 12:50:21 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	ft_assign_part_two(char *str, t_exp **lst, int status)
{
	t_exp	*this;
	char	**cut;

	cut = ft_strcut(str, '=', NULL);
	this = ft_lstchr(cut[0], *lst);
	if (this)
	{
		this->status = status;
		if (this->value && cut[1])
			ft_free_null((void **)&this->value);
		if (!this->value && cut[1])
			this->value = ft_strdup(cut[1]);
		else if (ft_ischar(str, '='))
		{
			ft_free_null((void **)&this->value);
			this->value = ft_strdup("");
		}
		ft_free_array_pointer(cut);
		return (0);
	}
	ft_free_array_pointer(cut);
	return (0);
}

static int	ft_assign_join_two(char *str, t_exp **lst, char **cut, int status)
{
	t_exp	*this;

	this = ft_lstchr(cut[0], *lst);
	if (this)
	{
		this->status = status;
		if (this->value && cut[1])
		{
			str = cut[1];
			cut[1] = ft_strjoin_gnl(this->value, cut[1]);
			ft_free_null((void **)&str);
			this->value = ft_strdup(cut[1]);
		}
		else if (cut[1] && !this->value)
			this->value = ft_strdup(cut[1]);
		else
			this->value = ft_strdup("");
		ft_free_array_pointer(cut);
		return (0);
	}
	ft_free_array_pointer(cut);
	return (0);
}

int	ft_assign_join(char *str, t_exp **lst, int status, char *swap)
{
	t_exp	*back;
	char	**cut;
	t_exp	*temp;

	cut = ft_strcut(str, '=', NULL);
	if (!cut)
		return (-1);
	swap = cut[0];
	cut[0] = ft_strtrim(swap, "+");
	ft_free_pointer(swap);
	temp = ft_lstchr(cut[0], *lst);
	if (temp)
		return (ft_assign_join_two(str, lst, cut, status));
	back = ft_newenv(cut[0], cut[1], status);
	if (!back)
		return (ft_free_array_pointer(cut) * -1);
	ft_free_array_pointer(cut);
	ft_addnew(lst, back);
	return (0);
}

int	ft_assign(char *str, t_exp **lst, int status)
{
	t_exp	*back;
	char	**cut;
	t_exp	*temp;

	cut = ft_strcut(str, '=', NULL);
	if (!cut)
		return (-1);
	if (cut[0] && cut[0][ft_strlen(cut[0]) - 1] == '+')
	{
		ft_free_array_pointer(cut);
		return (ft_assign_join(str, lst, status, NULL));
	}
	temp = ft_lstchr(cut[0], *lst);
	if (temp)
	{
		ft_free_array_pointer(cut);
		return (ft_assign_part_two(str, lst, status));
	}
	back = ft_newenv(cut[0], cut[1], status);
	if (!back)
		return (ft_free_array_pointer(cut) * -1);
	ft_free_array_pointer(cut);
	ft_addnew(lst, back);
	return (0);
}

int	ft_export(t_exp *lst)
{
	t_exp	*swap;

	swap = lst;
	signal(SIGPIPE, SIG_IGN);
	while (swap)
	{
		if (swap->status == 1)
		{
			if (swap->value)
				printf("export %s=\"%s\"\n", swap->alias, swap->value);
			else
				printf("export %s\n", swap->alias);
		}
		swap = swap->next;
	}
	return (0);
}
