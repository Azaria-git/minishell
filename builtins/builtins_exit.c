/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aravelom <aravelom@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:00:05 by aravelom          #+#    #+#             */
/*   Updated: 2025/09/10 16:14:11 by aravelom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	verbose_error(char *str)
{
	write (2, "exit\nminishell: exit :", 22);
	if (str)
		write (2, str, ft_strlen(str));
	write (2, ": numeric argument required\n", 29);
	return (2);
}

int	ft_isnumeric(char *str)
{
	int	i;
	int	len;

	if (!(*str))
		return (0);
	i = 0;
	len = ft_strlen(str);
	if (str[0] == '-' || str[0] == '+')
	{
		if (len > 20)
			return (0);
		i++;
	}
	if (i == 0 && len > 19)
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	ft_atuc_pipe(char **str)
{
	unsigned long long	result;
	signed long long	cast;
	int					i;

	cast = 0;
	if (ft_count_arg(str) == 1)
		return (0);
	if (ft_isnumeric(str[1]) == 0)
		return (verbose_error(str[1]));
	i = 0;
	if (str[1][0] == '+' || str[1][0] == '-')
		i++;
	while (str[1][i])
		cast = (cast * 10) + (str[1][i++] - '0');
	if (cast > LLONG_MAX || (str[1][0] == '-' && (cast * -1) < LLONG_MIN))
		return (verbose_error(str[1]));
	if (ft_count_arg(str) > 2)
	{
		ft_putendl_fd("exit\nminishell: exit : too many arguments", 2);
		return (1);
	}
	result = cast;
	if (str[1][0] == '-')
		result *= -1;
	return ((int)(result % 256));
}

static int	ft_atuc(char **str)
{
	unsigned long long	result;
	signed long long	cast;
	int					i;

	cast = 0;
	if (ft_count_arg(str) == 1)
		return (printf("exit\n") * 0);
	if (ft_isnumeric(str[1]) == 0)
		return (verbose_error(str[1]));
	i = 0;
	if (str[1][0] == '+' || str[1][0] == '-')
		i++;
	while (str[1][i])
		cast = (cast * 10) + (str[1][i++] - '0');
	if (cast > LLONG_MAX || (str[1][0] == '-' && (cast * -1) < LLONG_MIN))
		return (verbose_error(str[1]));
	if (ft_count_arg(str) > 2)
	{
		ft_putendl_fd("exit\nminishell: exit : too many arguments", 2);
		return (-1);
	}
	result = cast;
	if (str[1][0] == '-')
		result *= -1;
	return (printf("exit\n") / 5 * (int)(result % 256));
}

int	ft_exit(t_cmd **cmd, t_exp **exp, char **line, t_arg_child *args)
{
	int	exit_status;

	if (line)
	{
		exit_status = ft_atuc((*cmd)->args);
		if (exit_status < 0)
			return (1);
		if (line)
			ft_free_null((void **) line);
		if (exp)
			ft_clear_env(exp);
		if ((*cmd)->env)
			ft_free_split((*cmd)->env);
		if (cmd)
			free_cmd(cmd);
		exit(exit_status);
	}
	else
	{
		exit_status = ft_atuc_pipe((*cmd)->args);
		free_all(args);
		exit(exit_status);
	}
	return (0);
}
