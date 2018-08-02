/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addition2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oleshche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 11:47:12 by oleshche          #+#    #+#             */
/*   Updated: 2018/07/31 11:47:37 by oleshche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oleshche.h"

void	nullify_comment(char *args_str)
{
	ft_memset(ft_strchr(args_str, COMMENT_CHAR), 0,
			ft_strlen(ft_strchr(args_str, COMMENT_CHAR)));
	if (ft_isspace(args_str[ft_strlen(args_str) - 1]))
		spaces_clear(args_str);
}

int		label_name(void)
{
	t_label	*tmp;
	t_list	*global;
	int		i;

	global = g_list;
	while (global)
	{
		tmp = (t_label*)global->content;
		if (!tmp->label)
		{
			global = global->next;
			continue ;
		}
		if (tmp->label[ft_strlen(tmp->label) - 1] != LABEL_CHAR)
			return (1);
		i = 0;
		while (i < (int)ft_strlen(tmp->label) - 1)
			if (!ft_strchr(LABEL_CHARS, tmp->label[i++]))
				return (1);
		global = global->next;
	}
	return (NO_ERR);
}

int		next_label(char *line)
{
	char	**split;

	if (only_spaces(line))
		return (0);
	split = ft_split_whitespaces(line);
	if (line && *line && split[0][ft_strlen(split[0]) - 1] == LABEL_CHAR)
	{
		del_str_arr(split);
		return (1);
	}
	del_str_arr(split);
	return (0);
}

void	too_many_args(char **split, int flag, int *j, char **args)
{
	if (split[0] && split[1] && split[2] && split[3] && flag
		&& del_args(args, *j))
		*j = 0;
}

void	spaces_clear(char *str)
{
	int		i;

	i = (int)ft_strlen(str);
	while (ft_isspace(str[--i]))
		str[i] = 0;
}
