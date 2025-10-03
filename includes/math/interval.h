/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interval.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hguerrei <hguerrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 13:01:33 by hguerrei          #+#    #+#             */
/*   Updated: 2025/09/18 13:01:37 by hguerrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERVAL_H
# define INTERVAL_H
# include <stdbool.h>

typedef struct s_interval
{
	double	min;
	double	max;
}			t_interval;

double		interval_size(t_interval interval);
bool		interval_contains(double x, t_interval interval);
bool		interval_surrounds(double x, t_interval interval);
t_interval	interval_create(double min, double max);
double		clamp(double x, t_interval interval);
#endif