/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aravelom <aravelom@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:24:25 by marrandr          #+#    #+#             */
/*   Updated: 2025/09/12 11:58:02 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_assign_export(char *str, t_exp **lst)
{
	int		ret;

	ret = 0;
	if (error_export(str, "export"))
		return (1);
	ret = ft_assign(str, lst, 1);
	return (ret);
}

static int	ft_control_export(t_exp **lst, char **cmd, int nb_arg, int s)
{
	int	i;
	int	ret;

	i = 1;
	ret = -1;
	if (nb_arg == 1 && !ft_strncmp(cmd[0], "export", 7))
		ret = ft_export(*lst);
	else if (nb_arg == 2 && ft_strncmp(cmd[1], "-", 2) && cmd[1][0] == '-')
	{
		ft_putstr_fd("minishell: export: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putendl_fd(": invalid option", 2);
		return (2);
	}
	else if (nb_arg >= 2)
	{
		while (i < nb_arg)
		{
			ret = ft_assign_export(cmd[i++], lst);
			if (ret != 0)
				s = ret;
		}
	}
	return (s || ret);
}

static int	ft_control_assign(t_exp **lst, char **cmd, int nb_arg, char **s)
{
	int	i;
	int	ret;
	int	status;

	i = -1;
	ret = -1;
	status = 0;
	while (++i < nb_arg)
	{
		s = ft_strcut(cmd[i], '=', NULL);
		if ((s && syntax_error(s[0])) || !ft_ischar(cmd[i], '='))
		{
			ft_free_split(s);
			return (error_command(cmd[i]));
		}
		ft_free_split(s);
	}
	i = -1;
	while (++i < nb_arg)
	{
		ret = ft_assign(cmd[i], lst, 0);
		if (ret != 0)
			status = ret;
	}
	return (status || ret);
}

int	is_builins_cmd(char *cmd)
{
	if (!cmd)
		return (0);
	else if (!ft_strncmp(cmd, "exit", 5))
		return (2);
	else if (!ft_strncmp(cmd, "echo", 5))
		return (1);
	else if (!ft_strncmp(cmd, "cd", 3))
		return (2);
	else if (!ft_strncmp(cmd, "pwd", 4))
		return (1);
	else if (!ft_strncmp(cmd, "export", 7))
		return (1);
	else if (ft_ischar(cmd, '='))
		return (1);
	else if (!ft_strncmp(cmd, "unset", 6))
		return (2);
	else if (!ft_strncmp(cmd, "env", 4))
		return (1);
	else if (!ft_strncmp(cmd, ":", 2))
		return (2);
	else
		return (0);
}

int	in_builtins(t_cmd *arg, t_exp **lst, char **line, t_arg_child *args)
{
	int	ret;

	if (!ft_strncmp(arg->args[0], "exit", 5))
		ret = ft_exit(&arg, lst, line, args);
	else if (!ft_strncmp(arg->args[0], "echo", 5))
		ret = ft_echo(arg->args, 0);
	else if (!ft_strncmp(arg->args[0], "cd", 3))
		ret = ft_cd(arg->args, lst, NULL);
	else if (!ft_strncmp(arg->args[0], "pwd", 4))
		ret = ft_pwd(arg->args);
	else if (!ft_strncmp(arg->args[0], ":", 2))
		ret = 0;
	else if (!ft_strncmp(arg->args[0], "export", 7))
		ret = ft_control_export(lst, arg->args, ft_count_arg(arg->args), 0);
	else if (ft_ischar(arg->args[0], '='))
		ret = ft_control_assign(lst, arg->args, ft_count_arg(arg->args), NULL);
	else if (!ft_strncmp(arg->args[0], "unset", 6))
		ret = ft_unset(arg->args, *lst);
	else if (!ft_strncmp(arg->args[0], "env", 4))
		ret = ft_env(arg->args, *lst);
	else
		ret = -1;
	return (ret);
}
