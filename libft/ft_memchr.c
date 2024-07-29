/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:24:50 by nzharkev          #+#    #+#             */
/*   Updated: 2024/05/16 10:59:21 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(void const *ptr, int ch, size_t num)
{
	unsigned char	*t_ptr;
	size_t			i;

	i = 0;
	t_ptr = (unsigned char *) ptr;
	while (num > i)
	{
		if (*t_ptr == (unsigned char) ch)
			return (t_ptr);
		i++;
		t_ptr++;
	}
	return (NULL);
}
