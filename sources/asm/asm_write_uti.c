/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_write_uti.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandriie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 10:28:35 by yandriie          #+#    #+#             */
/*   Updated: 2018/07/25 13:10:37 by yandriie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_write.h"

static t_ops	find_op(char **src, t_track *tr)
{
	int		i;
	int		size;
	t_ops	tmp;

	i = 0;
	tr->s_pos = tr->w_pos;
	while (i < OPS_NUMBER)
	{
		tmp = get_op(i++);
		size = 0;
		while (!ft_isspace((*src)[size]))
			size++;
		if (!ft_strncmp(tmp.name, *src, size))
		{
			*src += (size + 1);
			while (ft_isspace(**src))
				(*src)++;
			return (tmp);
		}
	}
	return (tmp);
}

static int		find_codage(char *src)
{
	int		res;

	res = 0;
	while (*src && *src != COMMENT_CHAR)
	{
		if (*src == REGISTER_CHAR)
			res = (res + REG_CODE) << 2;
		else if (*src == DIRECT_CHAR)
			res = (res + DIR_CODE) << 2;
		else if (*src == '-' || ft_isdigit(*src) || *src == ':')
			res = (res + IND_CODE) << 2;
		src = skip(src);
	}
	while (res < 64)
		res = res << 2;
	return (res);
}

int				manage_code(int ofd, t_track *tr, char *src)
{
	int err;

	tr->op = find_op(&src, tr);
	tr->w_pos += push_buf(ofd, tr->op.op_code, OP_CODE_SIZE);
	tr->codage = find_codage(src) * tr->op.codage;
	tr->w_pos += (tr->codage ? push_buf(ofd, tr->codage, CODAGE_SIZE) : 0);
	while (*src && *src != COMMENT_CHAR)
	{
		tr->size = IND_CODE_SIZE;
		if (*src == REGISTER_CHAR && src++)
			tr->size = REG_CODE_SIZE;
		else if (*src == DIRECT_CHAR && src++)
		{
			tr->size = tr->op.label_size;
			if (*src == LABEL_CHAR)
				if ((err = lstadd(&(tr->to_find), ++src, tr)))
					return (err);
		}
		if (*src == LABEL_CHAR)
			if ((err = lstadd(&(tr->to_find), ++src, tr)))
				return (err);
		tr->w_pos += push_buf(ofd, ft_atoi(src), tr->size);
		src = skip(src);
	}
	return (0);
}

static char		*label_trim(char *str)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	while (ft_isspace(*str))
		str++;
	while (ft_strchr(LABEL_CHARS, str[i]))
		i++;
	if (!(res = (char *)ft_memalloc(sizeof(char) * (i + 1))))
		return (NULL);
	j = -1;
	while (++j < i)
		res[j] = str[j];
	res[j] = '\0';
	return (res);
}

int				lstadd(t_list_w **lst, char *str, t_track *tr)
{
	t_list_w	*tmp;

	tmp = *lst;
	if (!tmp)
	{
		if (!(tmp = (t_list_w *)ft_memalloc(sizeof(t_list_w))))
			return (MALLOC_ERR);
		*lst = tmp;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		if (!(tmp->next = (t_list_w *)ft_memalloc(sizeof(t_list_w))))
			return (MALLOC_ERR);
		tmp = tmp->next;
	}
	if (!(tmp->content = label_trim(str)))
		return (MALLOC_ERR);
	tmp->w_size = tr->size;
	tmp->w_pos = tr->w_pos;
	tmp->s_pos = tr->s_pos;
	return (NO_ERR);
}
