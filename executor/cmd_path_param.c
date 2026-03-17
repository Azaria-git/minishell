/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path_param.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aravelom <aravelom@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 09:17:44 by aravelom          #+#    #+#             */
/*   Updated: 2025/09/09 10:10:16 by aravelom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static char	**build_cmd_paths(char *path, char *cmd)
{
	int		y;
	char	**ret;
	char	*tmp;

	ret = NULL;
	y = 0;
	if (!cmd || !path)
		return (NULL);
	ret = ft_split_str(path + 5, ":");
	if (ret == NULL)
		return (NULL);
	tmp = ft_strjoin("/", cmd);
	while (ret[y])
	{
		ret[y] = ft_strjoin_gnl(ret[y], tmp);
		y++;
	}
	free(tmp);
	return (ret);
}

static void	wrait_error_path(const char *path, char *arg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd((char *)path, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(arg, 2);
	ft_putchar_fd('\n', 2);
}

static void	exit_mode(t_arg_child *args, int is_built, int exit_stat)
{
	if (is_built)
		return ;
	free_all(args);
	exit(exit_stat);
}

static int	check_exec_path(const char *path, t_arg_child *args, int is_built)
{
	struct stat	st;

	if (stat(path, &st) == -1)
	{
		wrait_error_path(path, strerror(errno));
		save_return_value(args->exp, 127);
		exit_mode(args, is_built, 127);
		return (-1);
	}
	if (S_ISDIR(st.st_mode))
	{
		wrait_error_path(path, "Is a directory");
		save_return_value(args->exp, 126);
		exit_mode(args, is_built, 126);
		return (-1);
	}
	if (access(path, X_OK) == -1)
	{
		wrait_error_path(path, "Permission denied");
		save_return_value(args->exp, 126);
		exit_mode(args, is_built, 126);
		return (-1);
	}
	return (0);
}

char	**cmd_path(char **env, char *cmd, t_arg_child *args, int is_built)
{
	char	**ret;

	ret = NULL;
	if (cmd == NULL)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (check_exec_path(cmd, args, is_built) != 0)
		{
			ft_free_split(env);
			return (NULL);
		}
		ret = (char **)malloc(sizeof(char *) * 2);
		if (!ret)
			return (NULL);
		ret[0] = ft_strdup(cmd);
		ret[1] = NULL;
		return (ret);
	}
	is_built = -1;
	while (env[++is_built])
		if (ft_strncmp(env[is_built], "PATH=", 5) == 0)
			break ;
	ret = build_cmd_paths(env[is_built], cmd);
	return (ret);
}
