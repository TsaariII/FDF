/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:26:32 by nzharkev          #+#    #+#             */
/*   Updated: 2024/05/16 11:00:35 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char const *s, int c)
{
	char	*ptr_s;
	char	ch;
	int		i;

	ptr_s = (char *)s;
	ch = (char)c;
	i = 0;
	while (ptr_s[i] != '\0')
		i++;
	while (i >= 0)
	{
		if (ptr_s[i] == ch)
			return (&ptr_s[i]);
		i--;
	}
	return (NULL);
}
