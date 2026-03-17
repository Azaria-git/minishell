/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aravelom <aravelom@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:22:39 by marrandr          #+#    #+#             */
/*   Updated: 2025/09/08 14:55:15 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_texp_size(t_exp *lst)
{
	int	i;

	if (!lst)
		return (0);
	i = 0;
	while (lst)
	{
		if (lst->status == 1)
			i++;
		lst = lst->next;
	}
	return (i);
}

char	**ft_env_to_tab(t_exp *lst)
{
	int		size;
	int		i;
	char	**env;
	char	*tmp;

	size = ft_texp_size(lst);
	env = malloc ((1 + size) * sizeof(char *));
	i = 0;
	while (i < size && lst)
	{
		if (lst->status == 1)
		{
			tmp = ft_strjoin_gnl(ft_strjoin(lst->alias, "="), lst->value);
			env[i++] = tmp;
		}
		lst = lst->next;
	}
	env[i] = NULL;
	return (env);
}

int	ft_env(char **arg, t_exp *lst)
{
	t_exp	*swap;

	if (ft_count_arg(arg) > 1)
	{
		ft_putendl_fd("env: too many arguments", 2);
		return (1);
	}
	swap = lst;
	while (swap)
	{
		if (swap->status == 1 && swap->value)
		{
			printf("%s=%s\n", swap->alias, swap->value);
		}
		swap = swap->next;
	}
	return (0);
}

void	ft_add_env(char **env, t_exp **lst)
{
	int		i;
	char	**split;
	t_exp	*elem;

	save_pid_value(lst);
	save_return_value(lst, 0);
	i = 0;
	while (env && env[i])
	{
		split = ft_strcut(env[i], '=', NULL);
		if (!split)
			return ;
		elem = ft_newenv(split[0], split[1], 1);
		if (!elem)
			return (ft_free_split(split));
		ft_free_split(split);
		ft_addnew(lst, elem);
		i++;
	}
}

int	ft_unset(char **arg, t_exp *lst)
{
	int		i;
	int		nb_arg;
	t_exp	*swap;
	int		ret;

	i = 1;
	ret = 0;
	nb_arg = ft_count_arg(arg);
	while (i < nb_arg)
	{
		swap = ft_lstchr(arg[i], lst);
		if (swap)
		{
			if (swap->value)
				free(swap->value);
			swap->value = NULL;
			swap->status = 0;
		}
		i++;
	}
	return (ret);
}
