/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:37:57 by nzharkev          #+#    #+#             */
/*   Updated: 2024/05/16 10:59:57 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char const *s, int c)
{
	while (*s != '\0' && *s != (char)c)
		s++;
	if (*s == (char)c)
		return ((char *) s);
	return (NULL);
}
