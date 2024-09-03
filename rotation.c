/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nzharkev <nzharkev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 13:48:04 by nzharkev          #+#    #+#             */
/*   Updated: 2024/09/03 14:16:50 by nzharkev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void    rotate_x(float *y, float *z, float *angle)
{
    float temp_y;
    float temp_z;

    temp_y = *y;
    temp_z = *z;

   *y = temp_y * cosf(angle) - temp_z * sinf(angle);
   *z = temp_y * sinf(angle) + temp_z * cosf(angle);
}

void    rotate_y(float *x, float *z, float angle)
{
    float temp_x;
    float temp_z;

    temp_x = *x;
    temp_z = *z;
    *x = temp_x * cosf(angle) + temp_z * sinf(angle);
    *z = -temp_x * sinf(angle) + temp_z * cosf(angle);
}

void    rotate_z(float *x, float *y, float angle)
{
    float temp_x;
    float temp_y;

    *x = temp_x * cosf(angle) - temp_y * sinf(angle);
    *y = temp_x * sinf(angle) + temp_y * cosf(angle);
}

void    projection(float *x, float *y, float *z)
{
    float temp_x;
    float temp_y;

    *x = (temp_x - temp_y) * cosf(30 * M_PI / 180);
    *y = (temp_x + temp_y) * sinf(30 * M_PI / 180);
}
