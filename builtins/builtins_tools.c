/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aravelom <aravelom@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:57:26 by marrandr          #+#    #+#             */
/*   Updated: 2025/08/25 14:54:29 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	save_pid_value(t_exp **lst)
{
	t_exp	*swap;
	char	*s_pid;
	int		pid;

	pid = getpid();
	s_pid = ft_itoa(pid);
	if (!s_pid)
		return ;
	swap = ft_lstchr("$$", *lst);
	if (!swap)
	{
		swap = ft_newenv("$$", s_pid, 2);
		if (!swap)
			return (free (s_pid));
		ft_addnew(lst, swap);
	}
	if (swap->value)
		free (swap->value);
	swap->value = s_pid;
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (tab[i])
		{
			free(tab[i]);
			tab[i] = NULL;
		}
		i++;
	}
}

int	ft_count_arg(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return (0);
	while (split[i])
		i++;
	return (i);
}

int	ft_ischar(const char *str, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	ft_free_pointer(void *arg)
{
	if (arg)
		free (arg);
	arg = NULL;
	return (1);
}
