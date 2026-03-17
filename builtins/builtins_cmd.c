/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aravelom <aravelom@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 14:08:33 by aravelom          #+#    #+#             */
/*   Updated: 2025/09/09 12:49:44 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_pwd(char **args)
{
	char	res[1024];

	if (ft_count_arg(args) > 1 && !ft_strncmp(args[1], "-", 1)
		&& ft_strncmp(args[1], "-", 2))
	{
		ft_putstr_fd("minishell: pwd: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(" :invalid option", 2);
		return (2);
	}
	if (getcwd(res, sizeof(res)) != NULL)
	{
		printf("%s\n", res);
		return (0);
	}
	else
		return (write_error(errno, NULL, "pwd"));
}

int	ft_check_newline(char **str, int *p)
{
	int	check;
	int	i;
	int	j;

	check = 0;
	i = 1;
	while (str[i])
	{
		if (str[i][0] == '-')
		{
			j = 1;
			while (str[i][j] && str[i][j] == 'n')
				j++;
			if (str[i][j] == 0 && j != 1)
				check++;
			else
				break ;
		}
		else
			break ;
		i++;
	}
	*p = check;
	return (i - 1);
}

int	ft_echo(char **str, int check)
{
	int	i;
	int	size;

	i = ft_check_newline(str, &check) + 1;
	size = ft_count_arg(str);
	while (i < size)
	{
		if (size > 2 && i != (check + 1))
		{
			printf(" ");
			printf("%s", str[i]);
		}
		else
			printf("%s", str[i]);
		i++;
	}
	if (check == 0)
		printf("\n");
	return (0);
}
