/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interval.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 14:01:22 by hguerrei          #+#    #+#             */
/*   Updated: 2025/06/16 18:22:21 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/interval.h"

/*
 * @brief Calculates the length of an interval.
 *
 * This function computes the size of an interval by finding the difference
 * between its maximum and minimum values.
 *
 * @param interval The interval structure containing min and max values.
 * @return The length of the interval (max - min).
 */
double  interval_size(t_interval interval)
{
    return (interval.max - interval.min);
}


/*
 * @brief Checks if a value is within an interval (inclusive of boundaries).
 *
 * This function determines whether the given value 'x' falls within the
 * specified interval, including the boundary values. It returns true if
 * x is greater than or equal to the minimum and less than or equal to the maximum.
 *
 * @param x The value to check.
 * @param interval The interval structure with min and max bounds.
 * @return true if x is inside the interval or on its boundaries, false otherwise.
 */
bool    interval_contains(double x,t_interval interval)
{
    return interval.min <= x && x <= interval.max;
}

t_interval interval_create(double min, double max)
{
    t_interval result;
    
    result.min = min;
    result.max = max;
    return (result);
}

/*
 * @brief Checks if a value is strictly within the bounds of an interval.
 *
 * This function returns true if the value 'x' is strictly greater than the minimum
 * and strictly less than the maximum of the given interval. The interval is defined
 * by its 'min' and 'max' fields.
 *
 * @param x The value to check.
 * @param interval The interval with 'min' and 'max' bounds.
 * @return true if x is strictly inside the interval (not on the bounds), false otherwise.
 */
bool    interval_surrounds(double x,t_interval interval)
{
        return interval.min < x && x < interval.max;
}


double  clamp(double x,t_interval interval)
{
    if(interval.min > x)
        return interval.min;
    if(x > interval.max)
        return interval.max;
    return x;
}
