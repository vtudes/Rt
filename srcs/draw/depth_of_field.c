/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   depth_of_field.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 22:57:49 by mlantonn          #+#    #+#             */
/*   Updated: 2018/07/26 12:53:22 by mlantonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"

static void	malloc_tabs(t_data *data, t_color *color_tabs[81])
{
	int i;
	int	j;

	i = -1;
	while (++i < 81)
		if (!(color_tabs[i] = (t_color *)malloc(32 * WIN_H * WIN_W)))
		{
			j = -1;
			perror("Error : ");
			while (++j < i)
				free(color_tabs[j]);
			exit_all(data);
		}
}

static void	fill2(t_vec pt, t_vec angle, t_color *color_tabs[81], t_point ij)
{
	char	*tmp;

	ft_putstr("\rDepth_of_field : %");
	tmp = ft_itoa((ij.x * 9 + ij.y) * 100 / 81);
	ft_putstr(tmp);
	free(tmp);
	angle.x = -g_data->dof_coeff + (g_data->dof_coeff * 0.25 * ij.y);
	g_data->cam = g_data->cams[g_data->i];
	rotate_around_point(g_data, pt, angle);
	if (g_data->clust_i == CLUST_CLIENT)
		g_data->cimg = (uint32_t*)color_tabs[ij.x * 9 + ij.y];
	else
		g_data->img->pxl = (uint32_t *)color_tabs[ij.x * 9 + ij.y];
	draw_image();
}

static void	fill_color_tabs(t_data *data, t_vec pt, t_color *color_tabs[81])
{
	uint32_t	*ptr;
	t_vec		angle;
	t_point		ij;

	ptr = data->clust_i == CLUST_CLIENT ? data->cimg : data->img->pxl;
	ij.x = -1;
	angle.z = 0;
	while (++ij.x < 9)
	{
		angle.y = -data->dof_coeff + (data->dof_coeff * 0.25 * ij.x);
		ij.y = -1;
		while (++ij.y < 9)
			fill2(pt, angle, color_tabs, ij);
	}
	ft_putstr("\rDepth_of_field : %100\n");
	if (data->clust_i == CLUST_CLIENT)
		data->cimg = ptr;
	else
		data->img->pxl = ptr;
}

static void	blend(uint32_t *img, t_color *color_tabs[81], int size)
{
	t_added	added;
	t_color	color;
	float	coeff;
	int		i;
	int		j;

	coeff = 81;
	i = -1;
	while (++i < size)
	{
		j = -1;
		added = (t_added){0, 0, 0, 0};
		while (++j < 81)
		{
			added.r += color_tabs[j][i].argb.r;
			added.g += color_tabs[j][i].argb.g;
			added.b += color_tabs[j][i].argb.b;
		}
		color.argb.r = added.r / coeff;
		color.argb.g = added.g / coeff;
		color.argb.b = added.b / coeff;
		color.argb.a = 255;
		img[i] = color.c;
	}
}

void		depth_of_field(void)
{
	t_color	*color_tabs[81];
	t_vec	point;
	int		i;

	point = g_data->objs[g_data->depth_of_field].pos;
	malloc_tabs(g_data, color_tabs);
	fill_color_tabs(g_data, point, color_tabs);
	blend(g_data->clust_i == CLUST_CLIENT ? g_data->cimg : g_data->img->pxl, \
			color_tabs, WIN_W * WIN_H);
	i = -1;
	while (++i < 81)
		free(color_tabs[i]);
}
