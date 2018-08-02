/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comment_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oleshche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 14:58:08 by oleshche          #+#    #+#             */
/*   Updated: 2018/07/02 14:58:12 by oleshche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oleshche.h"

static int	norminet_blyat(char *tmp, char **file, int i)
{
	if (ft_strchr(tmp + 1, '\"') - tmp - 1 <= COMMENT_LENGTH)
		return (clear_end(file, i, ft_strchr(tmp + 1, '\"') - file[i] + 1));
	return (print_err_msg(COMM_TOO_LONG, -1, -1));
}

int			check_comment_quotes(char **file, int i, int j)
{
	int		len;
	char	*tmp;

	while (ft_isspace(file[i][j]))
		j++;
	if (!ft_strnequ(&file[i][j], COMMENT_CMD_STRING, 8))
		return (print_err_msg(LEXICAL_ERR, i, j));
	j += 8;
	while (file[i][j] && file[i][j] != '\"')
		if (!ft_isspace(file[i][j++]))
			return (print_err_msg(SYNTAX_ERR, i, j));
	if ((tmp = &file[i][j]) && *tmp != '\"')
		return (print_err_msg(LEXICAL_ERR, i, (int)ft_strlen(file[i]) - 1));
	if (ft_strchr(tmp + 1, '\"'))
		return (norminet_blyat(tmp, file, i));
	len = (int)ft_strlen(tmp + 1) + 1;
	while (!(tmp = ft_strchr(file[++i], '\"')))
		len += (int)ft_strlen(file[i]) + 1;
	len += tmp - file[i];
	if (len > COMMENT_LENGTH)
		return (print_err_msg(COMM_TOO_LONG, -1, -1));
	return (clear_end(file, i, (int)(tmp - file[i]) + 1));
}

void		skip_name(char **file, int *i)
{
	char *tmp;

	tmp = ft_strchr(file[*i], '\"');
	if (ft_strchr(tmp + 1, '\"'))
		return ;
	else
	{
		(*i)++;
		while (1)
			if (ft_strchr(file[(*i)++], '\"'))
				break ;
	}
}

int			comment_check(char **file)
{
	int i;
	int j;

	i = -1;
	while (file[++i])
	{
		j = 0;
		while (ft_isspace(file[i][j]))
			j++;
		if (ft_strnequ(&file[i][j], NAME_CMD_STRING,
						ft_strlen(NAME_CMD_STRING)))
			skip_name(file, &i);
		if (file[i][j] != '#' && ft_strstr(file[i], COMMENT_CMD_STRING))
			break ;
		if (file[i][j] != '#' && !only_spaces(file[i]) &&
			!ft_strnequ(file[i], NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
			return (print_err_msg(SYNTAX_ERR, i, j));
	}
	return (check_comment_quotes(file, i, 0));
}
