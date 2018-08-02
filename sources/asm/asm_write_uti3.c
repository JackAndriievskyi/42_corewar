/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_write_uti3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandriie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 12:30:31 by yandriie          #+#    #+#             */
/*   Updated: 2018/07/13 08:12:45 by yandriie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_write.h"

int			is_name(char *str)
{
	int		size;

	while (ft_isspace(*str))
		str++;
	size = ft_strlen(NAME_CMD_STRING);
	if (!ft_strncmp(NAME_CMD_STRING, str, size))
		return (0);
	return (1);
}

int			is_comment(char *str)
{
	int		size;

	while (ft_isspace(*str))
		str++;
	size = ft_strlen(COMMENT_CMD_STRING);
	if (!ft_strncmp(COMMENT_CMD_STRING, str, size))
		return (0);
	return (1);
}

static int	get_rest_text(int ifd, char *dst, int *j)
{
	char	*line;
	int		i;
	int		err;
	int		f;

	f = 0;
	while (!f && (err = get_next_line(ifd, &line)) > 0)
	{
		dst[(*j)++] = '\n';
		i = 0;
		while (line[i] != DQUOTE_CHR && line[i] != '\0')
			dst[(*j)++] = line[i++];
		if (line[i] == DQUOTE_CHR)
			f--;
		free(line);
	}
	if (err < 0)
		return (MALLOC_ERR);
	return (NO_ERR);
}

int			get_text(char *src, int ifd, char *dst, int f)
{
	int		i;
	int		j;

	i = 0;
	while (src[i] != DQUOTE_CHR)
		i++;
	i++;
	j = 0;
	while (src[i] != DQUOTE_CHR && src[i] != '\0')
		dst[j++] = src[i++];
	if (src[i] != DQUOTE_CHR)
	{
		if (get_rest_text(ifd, dst, &j))
			return (MALLOC_ERR);
		while (!f && j < PROG_NAME_LENGTH)
			dst[j++] = 0;
		while (f && j < COMMENT_LENGTH)
			dst[j++] = 0;
	}
	free(src);
	return (NO_ERR);
}

void		push_header(int ofd, t_track *tracker)
{
	int		i;

	tracker->w_pos += push_buf(ofd, tracker->header.magic, MAGIC_SIZE);
	i = 0;
	while (i < PROG_NAME_LENGTH)
		tracker->w_pos += push_buf(ofd, tracker->header.prog_name[i++], 1);
	tracker->w_pos += push_buf(ofd, BLANK_SPACE, BLANK_SPACE_SIZE);
	tracker->w_pos += push_buf(ofd, BLANK_SPACE, BLANK_SPACE_SIZE);
	i = 0;
	while (i < COMMENT_LENGTH)
		tracker->w_pos += push_buf(ofd, tracker->header.comment[i++], 1);
	tracker->w_pos += push_buf(ofd, BLANK_SPACE, BLANK_SPACE_SIZE);
}
