/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 11:00:50 by nzharkev          #+#    #+#             */
/*   Updated: 2024/05/27 14:56:05 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(char const *str, ...)
{
	int		num_c;
	int		check;
	va_list	args;

	num_c = 0;
	check = 0;
	va_start(args, str);
	num_c = check_form(str, args, &check);
	if (check == -1)
	{
		va_end(args);
		return (-1);
	}
	va_end(args);
	return (num_c);
}
