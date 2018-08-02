/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oleshche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 10:31:49 by oleshche          #+#    #+#             */
/*   Updated: 2018/08/01 12:41:16 by yandriie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oleshche.h"

int		t_reg_arg(char *arg_orig)
{
	int		reg;
	int		i;
	int		j;

	if (!arg_orig)
		return (0);
	i = 0;
	if (arg_orig[0] != REGISTER_CHAR
		|| !arg_orig[++i]
		|| ft_strlen(arg_orig + i) > 2)
		return (0);
	j = 1;
	while (arg_orig[j])
		if (!ft_isdigit(arg_orig[j++]))
			return (0);
	reg = ft_atoi(arg_orig + i);
	return (reg >= 0 && reg <= 99 ? 1 : 0);
}

int		search_label(char *label_name)
{
	t_label	lb;
	t_list	*tmp;

	if (!*label_name)
		return (0);
	tmp = g_list;
	while (tmp)
	{
		lb = *(t_label*)tmp->content;
		if (!lb.label)
		{
			tmp = tmp->next;
			continue ;
		}
		if (ft_strnequ(lb.label, label_name, ft_strlen(lb.label) - 1)
			&& ft_strlen(lb.label) - 1 == ft_strlen(label_name))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int		t_dir_arg(char *arg_orig)
{
	int		i;

	if (!arg_orig)
		return (0);
	i = 0;
	if (arg_orig[i] != DIRECT_CHAR || !arg_orig[++i])
		return (0);
	if (arg_orig[i] == LABEL_CHAR)
	{
		i = search_label(arg_orig + i + 1);
		return (i);
	}
	if (arg_orig[i] == '-')
		i++;
	while (arg_orig[i])
		if (!ft_isdigit(arg_orig[i++]))
			return (0);
	return (i >= 2 ? 1 : 0);
}

int		t_ind_arg(char *arg_orig)
{
	int		i;
	short	minus;

	if (!arg_orig)
		return (0);
	i = 0;
	minus = 0;
	if (arg_orig[i] == LABEL_CHAR)
	{
		i = search_label(arg_orig + i + 1);
		return (i);
	}
	if (arg_orig[i] == '-' && (++minus))
		i++;
	if (ft_strlen(arg_orig) >= 1)
		while (arg_orig[i])
			if (!ft_isdigit(arg_orig[i++]))
				return (0);
	return (i > 1 || (i == 1 && !minus) ? 1 : 0);
}
