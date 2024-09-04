/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:48:04 by nzharkev          #+#    #+#             */
/*   Updated: 2024/09/04 13:37:52 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fdf.h"

void    rotate_x(float *y, float *z)
{
    float temp_y;
    float temp_z;
    float angle;

    temp_y = *y;
    temp_z = *z;
    angle = X_ANGLE * M_PI / 180;

   *y = temp_y * cosf(angle) - temp_z * sinf(angle);
   *z = temp_y * sinf(angle) + temp_z * cosf(angle);
}

void    rotate_y(float *x, float *z)
{
    float temp_x;
    float temp_z;
    float angle;

    temp_x = *x;
    temp_z = *z;
    angle = Y_ANGLE * M_PI / 180;
    *x = temp_x * cosf(angle) + temp_z * sinf(angle);
    *z = -temp_x * sinf(angle) + temp_z * cosf(angle);
}

void    rotate_z(float *x, float *y)
{
    float temp_x;
    float temp_y;
    float angle;

    temp_x = *x;
    temp_y = *y;
    angle = Z_ANGLE * M_PI / 180;
    *x = temp_x * cosf(angle) - temp_y * sinf(angle);
    *y = temp_x * sinf(angle) + temp_y * cosf(angle);
}

void    projection(float *x, float *y, float z)
{
    float temp_x;
    float temp_y;

    temp_x = *x;
    temp_y = *y;
    *x = (temp_x - temp_y) * cosf(30 * M_PI / 180);
    *y = (temp_x + temp_y) * sinf(30 * M_PI / 180) - z;
}
