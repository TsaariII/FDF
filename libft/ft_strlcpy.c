/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:00:29 by nzharkev          #+#    #+#             */
/*   Updated: 2024/05/16 11:00:17 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, char const *src, size_t size)
{
	size_t	s;
	size_t	len_src;

	s = 0;
	len_src = ft_strlen(src);
	if (size == 0)
		return (len_src);
	while (s < size - 1 && src[s])
	{
		dest[s] = src[s];
		s++;
	}
	dest[s] = '\0';
	return (len_src);
}
