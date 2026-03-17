/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marrandr <marrandr@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:56:35 by marrandr          #+#    #+#             */
/*   Updated: 2025/08/04 11:22:49 by marrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_history.h"
#include <stdlib.h>

static int	count_line_history(const char *path_file)
{
	int		fd;
	char	*line;
	int		i;

	fd = open (path_file, O_RDONLY);
	if (fd < 0)
		return (-1);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		free (line);
		i++;
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	close (fd);
	return (i);
}

void	manage_file_hitory(const char *path_file)
{
	int		pipefd[2];
	int		fd;
	char	buff[1];

	if (count_line_history(path_file) < MAX_HISTORY_LEN)
		return ;
	if (pipe (pipefd) == -1)
		return ;
	fd = open (path_file, O_RDONLY);
	if (fd < 0)
		return ;
	read (fd, buff, 1);
	while (buff[0] != '\n')
		read (fd, buff, 1);
	while (read (fd, buff, 1) != 0)
		write (pipefd[1], buff, 1);
	close (pipefd[1]);
	close (fd);
	fd = open(path_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return ;
	while (read (pipefd[0], buff, 1))
		write (fd, buff, 1);
	close (pipefd[0]);
	close (fd);
}

void	init_history(const char *path_file)
{
	char	*temp;
	char	*line;
	int		fd;

	if (access(path_file, F_OK | R_OK) == -1)
		return ;
	fd = open(path_file, O_RDONLY);
	if (fd < 0)
		return ;
	line = get_next_line(fd);
	while (line)
	{
		temp = line;
		line = ft_strtrim(line, "\n");
		free (temp);
		add_history(line);
		free (line);
		line = get_next_line(fd);
	}
	if (line)
		free (line);
	close (fd);
}

void	save_infile_history(const char *path_file, const char *line)
{
	int	fd;

	manage_file_hitory(path_file);
	if (access(path_file, F_OK | W_OK) == -1)
		fd = open(path_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(path_file, O_WRONLY | O_APPEND);
	if (fd < 0)
		return ;
	write (fd, line, ft_strlen((char *)line));
	write (fd, "\n", 1);
	close (fd);
}
