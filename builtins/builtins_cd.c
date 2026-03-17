/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 13:45:19 by marrandr          #+#    #+#             */
/*   Updated: 2025/09/10 17:42:57 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static char	*get_value_env(t_exp *exp, char *alias)
{
	t_exp	*temp;
	char	*res;

	temp = ft_lstchr(alias, exp);
	if (!temp || !(temp->value))
		return (ft_strdup(""));
	res = ft_strdup(temp->value);
	return (res);
}

static void	update_old_new_pwd(t_exp **exp)
{
	char	dir_now[1024];
	char	*dir_old;

	dir_old = get_value_env(*exp, "PWD");
	ft_assign_export_local("OLDPWD", dir_old, exp);
	ft_free_pointer(dir_old);
	if (getcwd(dir_now, sizeof(dir_now)))
		ft_assign_export_local("PWD", dir_now, exp);
}

int	ft_cd(char **args, t_exp **lst, char *str)
{
	char	dirnow[1024];
	int		nb;

	nb = ft_count_arg(args);
	if (nb == 1)
		return (write (2, "minishell: cd: missing path\n", 28) / 28);
	else if (nb == 2)
		str = ft_strdup(args[1]);
	else if (nb > 2)
		return (write (2, "minishell: cd: too many arguments\n", 34) / 34);
	if (str && ft_strlen(str) == 0)
		return (ft_free_pointer(str) * 0);
	if (str && (!getcwd(dirnow, sizeof(dirnow)) || chdir(str) == -1))
	{
		write_error(errno, str, args[0]);
		return (ft_free_pointer(str));
	}
	if (str)
		ft_free_pointer(str);
	update_old_new_pwd(lst);
	return (0);
}
