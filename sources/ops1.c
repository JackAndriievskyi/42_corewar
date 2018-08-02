/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandriie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 08:50:16 by yandriie          #+#    #+#             */
/*   Updated: 2018/07/13 09:33:41 by yandriie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

#define OPS_NUMBER 16

static void		init1(t_ops *ops)
{
	ops[0].op_code = 1;
	ops[0].name = "live";
	ops[0].args[0] = T_DIR;
	ops[0].cycles = 10;
	ops[1].op_code = 2;
	ops[1].name = "ld";
	ops[1].args[0] = T_DIR + T_IND;
	ops[1].args[1] = T_REG;
	ops[1].cycles = 5;
	ops[2].op_code = 3;
	ops[2].name = "st";
	ops[2].args[0] = T_REG;
	ops[2].args[1] = T_REG + T_IND;
	ops[2].cycles = 5;
	ops[3].op_code = 4;
	ops[3].name = "add";
	ops[3].args[0] = T_REG;
	ops[3].args[1] = T_REG;
	ops[3].args[2] = T_REG;
	ops[3].cycles = 10;
	ops[4].op_code = 5;
	ops[4].name = "sub";
	ops[4].args[0] = T_REG;
	ops[4].args[1] = T_REG;
	ops[4].args[2] = T_REG;
}

static void		init2(t_ops *ops)
{
	ops[4].cycles = 10;
	ops[5].op_code = 6;
	ops[5].name = "and";
	ops[5].args[0] = T_REG + T_DIR + T_IND;
	ops[5].args[1] = T_REG + T_DIR + T_IND;
	ops[5].args[2] = T_REG;
	ops[5].cycles = 6;
	ops[6].op_code = 7;
	ops[6].name = "or";
	ops[6].args[0] = T_REG + T_DIR + T_IND;
	ops[6].args[1] = T_REG + T_DIR + T_IND;
	ops[6].args[2] = T_REG;
	ops[6].cycles = 6;
	ops[7].op_code = 8;
	ops[7].name = "xor";
	ops[7].args[0] = T_REG + T_DIR + T_IND;
	ops[7].args[1] = T_REG + T_DIR + T_IND;
	ops[7].args[2] = T_REG;
	ops[7].cycles = 6;
	ops[8].op_code = 9;
	ops[8].name = "zjmp";
	ops[8].args[0] = T_DIR;
	ops[8].cycles = 20;
	ops[9].op_code = 10;
	ops[9].name = "ldi";
}

static void		init3(t_ops *ops)
{
	ops[9].args[0] = T_REG + T_DIR + T_IND;
	ops[9].args[1] = T_REG + T_DIR;
	ops[9].args[2] = T_REG;
	ops[9].cycles = 25;
	ops[10].op_code = 11;
	ops[10].name = "sti";
	ops[10].args[0] = T_REG;
	ops[10].args[1] = T_REG + T_DIR + T_IND;
	ops[10].args[2] = T_REG + T_DIR;
	ops[10].cycles = 25;
	ops[11].op_code = 12;
	ops[11].name = "fork";
	ops[11].args[0] = T_DIR;
	ops[11].cycles = 800;
	ops[12].op_code = 13;
	ops[12].name = "lld";
	ops[12].args[0] = T_DIR + T_IND;
	ops[12].args[1] = T_REG;
	ops[12].cycles = 10;
	ops[13].op_code = 14;
	ops[13].name = "lldi";
	ops[13].args[0] = T_REG + T_DIR + T_IND;
	ops[13].args[1] = T_REG + T_DIR;
	ops[13].args[2] = T_REG;
	ops[13].cycles = 50;
}

static void		init4(t_ops *ops)
{
	int		i;

	ops[14].op_code = 15;
	ops[14].name = "lfork";
	ops[14].args[0] = T_DIR;
	ops[14].cycles = 1000;
	ops[15].op_code = 16;
	ops[15].name = "aff";
	ops[15].args[0] = T_REG;
	ops[15].cycles = 2;
	i = 0;
	while (i < OPS_NUMBER)
	{
		ops[i].label_size = (((i >= 0 && i < 8) || i == 12 || i == 16) ? 4 : 2);
		ops[i].carry = ((i < 3 || i > 13 || (i > 7 && i < 12)) ? 0 : 1);
		ops[i].codage = ((i == 0 || i == 8 || i == 11 || i == 14) ? 0 : 1);
		i++;
	}
	ops[1].carry = 1;
}

t_ops			get_op(unsigned int code)
{
	static t_ops	ops[OPS_NUMBER];
	int				i;

	if (ops[0].op_code == 0)
	{
		i = 0;
		while (i < OPS_NUMBER)
		{
			ops[i].args[0] = 0;
			ops[i].args[1] = 0;
			ops[i].args[2] = 0;
			i++;
		}
		init1(ops);
		init2(ops);
		init3(ops);
		init4(ops);
	}
	return (ops[code]);
}
