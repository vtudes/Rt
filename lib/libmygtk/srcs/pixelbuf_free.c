/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixelbuf_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 18:49:41 by fchevrey          #+#    #+#             */
/*   Updated: 2018/06/27 19:07:41 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mygtk.h"

void	pixelbuf_free(t_pixelbuf **pxlbuf)
{
	if (pxlbuf && *pxlbuf)
	{
		g_object_unref((*pxlbuf)->buf);
		free(*pxlbuf);
		*pxlbuf = NULL;
	}
}
