/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oleshche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 18:31:46 by oleshche          #+#    #+#             */
/*   Updated: 2018/07/01 18:31:53 by oleshche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oleshche.h"

int			clear_end(char **file, int i, int j)
{
	while (ft_isspace(file[i][j]))
		j++;
	if (file[i][j] == '\0' || file[i][j] == '#')
		return (NO_ERR);
	return (print_err_msg(SYNTAX_ERR, i, j));
}

static int	norminet_blyat2(char *tmp, char **file, int i, int j)
{
	if (tmp - &file[i][j] - 1 <= PROG_NAME_LENGTH)
		return (clear_end(file, i, (int)(tmp - file[i]) + 1));
	return (print_err_msg(NAME_TOO_LONG, -1, -1));
}

int			check_name_quotes(char **file, int i, int j)
{
	int		len;
	char	*tmp;

	while (ft_isspace(file[i][j]))
		j++;
	if (!ft_strnequ(&file[i][j], NAME_CMD_STRING, 5))
		return (print_err_msg(LEXICAL_ERR, i, j));
	j += 5;
	while (file[i][j] && file[i][j] != '\"')
		if (!ft_isspace(file[i][j++]))
			return (print_err_msg(SYNTAX_ERR, i, j));
	if ((tmp = &file[i][j]) && *tmp != '\"')
		return (print_err_msg(LEXICAL_ERR, i, (int)ft_strlen(file[i]) - 1));
	if ((tmp = ft_strchr(tmp + 1, '\"')))
		return (norminet_blyat2(tmp, file, i, j));
	len = (int)ft_strlen(&file[i][j] + 1) + 1;
	while (!(tmp = ft_strchr(file[++i], '\"')))
		len += (int)ft_strlen(file[i]) + 1;
	len += tmp - file[i];
	if (len > PROG_NAME_LENGTH)
		return (print_err_msg(NAME_TOO_LONG, -1, -1));
	return (clear_end(file, i, (int)(tmp - file[i]) + 1));
}

void		skip_comment(char **file, int *i)
{
	char	*tmp;

	tmp = ft_strchr(file[*i], '\"');
	if (ft_strchr(tmp + 1, '\"'))
		return ;
	else
	{
		(*i)++;
		while (1)
			if (ft_strchr(file[((*i)++)], '\"'))
				break ;
	}
}

int			name_check(char **file)
{
	int	i;
	int	j;

	i = -1;
	while (file[++i])
	{
		j = 0;
		while (ft_isspace(file[i][j]))
			j++;
		if (ft_strnequ(&file[i][j], COMMENT_CMD_STRING,
			ft_strlen(COMMENT_CMD_STRING)))
			skip_comment(file, &i);
		if (file[i][j] != COMMENT_CHAR && ft_strstr(file[i], NAME_CMD_STRING))
			break ;
		if (file[i][j] != COMMENT_CHAR && !only_spaces(file[i]) &&
			!ft_strnequ(&file[i][j], COMMENT_CMD_STRING,
			ft_strlen(COMMENT_CMD_STRING)))
			return (print_err_msg(LEXICAL_ERR, i, j));
	}
	return (check_name_quotes(file, i, 0));
}
