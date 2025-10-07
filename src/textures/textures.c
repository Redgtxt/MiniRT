/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ruigoncalves <ruigoncalves@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 15:46:56 by ruigoncalve       #+#    #+#             */
/*   Updated: 2025/10/03 16:12:58 by ruigoncalve      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

bool	scatter(const t_material *mat, const t_ray *r_in, t_hit_record *rec,
		t_data_scatter *data_scatter)
{
	if (mat->type == LAMBERTIAN)
		return (lambertian_scatter(rec, data_scatter));
	else if (mat->type == METAL)
		return (metal_scatter(r_in, rec, data_scatter));
	else if (mat->type == CHECKERPATTERN)
		return (checker_scatter(rec, data_scatter));
	else if (mat->type == GLASS)
		return (glass_scatter(r_in, rec, data_scatter));
	return (false);
}
