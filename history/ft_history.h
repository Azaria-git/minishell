/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aravelom <aravelom@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:18:41 by marrandr          #+#    #+#             */
/*   Updated: 2025/08/04 11:35:44 by aravelom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HISTORY_H
# define FT_HISTORY_H
# include <readline/history.h>
# include <unistd.h>
# include <fcntl.h>
# include "../Libft/libft.h"
# define MINISHELL_HISTORY ".minishell_history"
# define MAX_HISTORY_LEN 100

void	init_history(const char *path_file);
void	save_infile_history(const char *path_file, const char *line);

#endif
