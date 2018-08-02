/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_write_uti2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandriie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 08:35:28 by yandriie          #+#    #+#             */
/*   Updated: 2018/07/25 14:06:29 by yandriie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_write.h"

int		is_empty(char *str)
{
	while (ft_isspace(*str))
		str++;
	if (*str && *str != COMMENT_CHAR)
		return (1);
	return (0);
}

int		is_label(char *str)
{
	while (ft_isspace(*str))
		str++;
	if (!ft_strchr(LABEL_CHARS, *str))
		return (1);
	while (ft_strchr(LABEL_CHARS, *str))
		str++;
	if (*str != LABEL_CHAR)
		return (1);
	return (0);
}

char	*skiplabel(char *str)
{
	while (ft_isspace(*str))
		str++;
	if (!is_label(str))
	{
		while (*str != LABEL_CHAR)
			str++;
		str++;
		while (ft_isspace(*str))
			str++;
	}
	return (str);
}

char	*skip(char *str)
{
	if (*str == '-' || *str == DIRECT_CHAR)
		str++;
	if (*str == LABEL_CHAR || *str == '-')
		str++;
	while (*str && ft_strchr(LABEL_CHARS, *str))
		str++;
	while (ft_isspace(*str))
		str++;
	if (*str == SEPARATOR_CHAR)
		str++;
	while (ft_isspace(*str))
		str++;
	return (str);
}

int		find_val(t_list_w *to_find, t_list_w *available)
{
	while (available)
	{
		if (!ft_strcmp(to_find->content, available->content))
			return (available->w_pos - to_find->s_pos);
		available = available->next;
	}
	return (0);
}
