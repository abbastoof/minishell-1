/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atoof <atoof@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 15:33:21 by atoof             #+#    #+#             */
/*   Updated: 2023/05/20 17:14:30 by atoof            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_realloc(char **ptr, size_t size)
{
	size_t		i;
	char		**new;

	i = 0;
	while (ptr[i])
		i++;
	if (size <= i)
		return (ptr);
	new = ft_calloc(sizeof(char *), size + 1);
	if (!new)
		return (ptr);
	new = ft_memcpy(new, ptr, i * sizeof(char *));
	i = 0;
	return (new);
}