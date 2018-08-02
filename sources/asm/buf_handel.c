/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf_handel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandriie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 09:36:05 by yandriie          #+#    #+#             */
/*   Updated: 2018/07/25 10:33:15 by yandriie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm_write.h"
#include "asm.h"

static char	g_buf[ASM_BUFF_SIZE];
static int	g_cnt;

void		clean_buf(int ofd)
{
	write(ofd, g_buf, g_cnt);
	g_cnt = 0;
}

int			push_buf(int ofd, int val, int size)
{
	t_val	eval;
	int		i;

	eval.ival = val;
	i = 0;
	while (i < size)
	{
		if (g_cnt >= ASM_BUFF_SIZE)
			clean_buf(ofd);
		g_buf[g_cnt++] = eval.bval[size - 1 - i++];
	}
	return (size);
}
