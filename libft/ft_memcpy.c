/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:47:04 by nzharkev          #+#    #+#             */
/*   Updated: 2024/05/16 10:59:27 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, void const *src, size_t n)
{
	unsigned char	*tdest;
	unsigned char	*tsrc;

	tdest = (unsigned char *) dest;
	tsrc = (unsigned char *) src;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (n > 0)
	{
		*tdest = *tsrc;
		tdest++;
		tsrc++;
		n--;
	}
	return (dest);
}
