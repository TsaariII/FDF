/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:25:17 by nzharkev          #+#    #+#             */
/*   Updated: 2024/10/03 10:31:33 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t old, size_t new)
{
	void	*new_ptr;
	size_t	copy;

	new_ptr = malloc(new);
	if (!new_ptr)
	{
		free(ptr);
		return (NULL);
	}
	if (old < new)
		copy = old;
	else
		copy = new;
	if (ptr)
	{
		ft_memcpy(new_ptr, ptr, copy);
		free(ptr);
	}
	return (new_ptr);
}
