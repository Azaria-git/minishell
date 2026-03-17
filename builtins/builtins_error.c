/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aravelom <aravelom@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:58:38 by marrandr          #+#    #+#             */
/*   Updated: 2025/09/12 07:12:03 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	count_char_diff(char *s, char *a, int i, int nb)
{
	int		tab[53];

	if (!s)
		return (0);
	a = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_";
	if (!a)
		return (0);
	i = 0;
	ft_memset(tab, 0, sizeof(tab));
	while (s[i])
	{
		if (ft_strchr(a, s[i]))
		{
			nb = ft_strchr(a, s[i]) - a;
			if (nb > 0 && nb < 53)
				tab[nb] = 1;
		}
		i++;
	}
	i = 0;
	nb = 0;
	while (i < 53)
		nb += tab[i++];
	return (nb);
}

int	write_error(int er, char *info, char *cmd)
{
	char	*msg;

	msg = strerror(er);
	write(2, "minishell: ", 12);
	if (cmd)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
	}
	if (info)
	{
		write(2, info, ft_strlen(info));
		write(2, ": ", 2);
	}
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	if (er == ENOENT)
		return (127);
	if (er == EACCES || er == EISDIR)
		return (126);
	else
		return (1);
}

int	syntax_error(char *str)
{
	int		i;
	char	**cut;

	if (!str)
		return (1);
	if (str[0] != '_' && !ft_isalpha(str[0]))
		return (1);
	cut = ft_strcut(str, '=', NULL);
	if (!cut)
		return (1);
	i = 0;
	while (cut && cut[0][i])
	{
		if (!cut[0][i + 1] && cut[0][i] == '+')
			break ;
		if (cut[0][i] != '_' && !ft_isalnum(cut[0][i]))
		{
			ft_free_split(cut);
			return (1);
		}
		i++;
	}
	ft_free_split(cut);
	return (0);
}

int	error_export(char *str, char *cmd)
{
	if (syntax_error(str))
	{
		write (2, "minishell: ", 11);
		if (!cmd)
		{
			write (2, str, ft_strlen(str));
			write(2, ": command not found\n", 20);
			return (127);
		}
		write (2, cmd, ft_strlen(cmd));
		write (2, ": ", 2);
		write (2, str, ft_strlen(str));
		write (2, ": not a valid identifier\n", 25);
		return (1);
	}
	return (0);
}

int	error_command(char *cmd)
{
	write (2, "minishell: ", 11);
	write (2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 20);
	return (127);
}
