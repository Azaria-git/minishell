/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aravelom <aravelom@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 20:19:36 by aravelom          #+#    #+#             */
/*   Updated: 2025/08/05 13:24:17 by aravelom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**free_tokens(char **tokens)
{
	ssize_t	y;

	y = 0;
	while (tokens[y])
	{
		free(tokens[y]);
		y++;
	}
	free(tokens);
	return (NULL);
}
