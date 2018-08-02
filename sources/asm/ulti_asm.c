/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utli_asm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandriie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 08:18:44 by yandriie          #+#    #+#             */
/*   Updated: 2018/06/26 08:19:56 by yandriie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oleshche.h"

int		skip_start_in(char **file, int *i, int *j)
{
	if (!ft_strncmp(&file[*i][*j], NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
	{
		skip_name(file, i);
		if (file[*i] && !ft_strncmp(&file[*i][*j], NAME_CMD_STRING,
									ft_strlen(NAME_CMD_STRING)))
			(*i)++;
		return (1);
	}
	else if (file[*i] && !ft_strncmp(&file[*i][*j], COMMENT_CMD_STRING,
										ft_strlen(COMMENT_CMD_STRING)))
	{
		skip_comment(file, i);
		if (!ft_strncmp(&file[*i][*j], COMMENT_CMD_STRING,
						ft_strlen(COMMENT_CMD_STRING)))
			(*i)++;
		return (1);
	}
	return (0);
}

int		skip_start(char **file)
{
	int	i;
	int	j;

	i = 0;
	while (file[i] && !(j = 0))
	{
		while (ft_isspace(file[i][j]))
			j++;
		if (file[i][j] == COMMENT_CHAR || only_spaces(file[i]))
			i++;
		else if (skip_start_in(file, &i, &j))
			continue ;
		else
			break ;
	}
	return (i);
}

t_ops	find_info(char *name)
{
	int		i;
	t_ops	info;

	i = -1;
	while (++i < 16)
	{
		info = get_op((unsigned int)i);
		if (ft_strequ(name, info.name))
			return (info);
	}
	return (*((t_ops*)ft_memset(&info, 0, sizeof(t_ops))));
}

int		del_args(char **args, int j)
{
	int	i;

	i = 0;
	while (args[i] && i < 3 && i < j)
		free(args[i++]);
	return (1);
}
