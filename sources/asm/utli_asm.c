/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utli_asm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandriie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 08:18:44 by yandriie          #+#    #+#             */
/*   Updated: 2018/08/01 15:56:00 by yandriie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			print_err_msg(int err, int arg1, int arg2)
{
	if (err == USAGE_ERR)
		ft_putendl(USAGE_ERR_MSG);
	if (err == MALLOC_ERR)
		ft_putendl(MALLOC_ERR_MSG);
	if (err == OPEN_ERR)
		ft_putendl(OPEN_ERR_MSG);
	if (err == SYNTAX_ERR)
		ft_putendl(SYNTAX_ERR_MSG);
	if (err == NAME_TOO_LONG)
		ft_putendl(NAME_TOO_LONG_MSG);
	if (err == COMM_TOO_LONG)
		ft_putendl(COMM_TOO_LONG_MSG);
	if (err == LEXICAL_ERR)
		ft_putendl(LEXICAL_ERR_MSG);
	if (err == FILE_ERR)
		ft_putendl(FILE_ERR_MSG);
	arg1++;
	arg2++;
	return (err);
}

void		print_ok_msg(char *msg)
{
	ft_putstr(FINAL_OK_MSG);
	ft_putendl(msg);
}
