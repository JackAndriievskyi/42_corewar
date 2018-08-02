/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_this_out.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandriie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 08:54:43 by yandriie          #+#    #+#             */
/*   Updated: 2018/07/26 08:37:32 by yandriie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "asm_write.h"

static int		write_header(int ofd, int ifd, t_track *tracker)
{
	char	*line;
	int		err;
	int		flag;

	tracker->header.magic = COREWAR_EXEC_MAGIC;
	flag = 2;
	while (flag && (err = get_next_line(ifd, &line)) > 0)
	{
		if (is_empty(line))
		{
			flag--;
			if (!is_name(line))
				if ((err = get_text(line, ifd, tracker->header.prog_name, 0)))
					return (err);
			if (!is_comment(line))
				if ((err = get_text(line, ifd, tracker->header.comment, 1)))
					return (err);
		}
		else
			free(line);
	}
	if (err < 0)
		return (MALLOC_ERR);
	push_header(ofd, tracker);
	return (NO_ERR);
}

static int		write_execode(int ofd, int ifd, t_track *tracker)
{
	char	*line;
	int		err;
	char	*ptr;

	while ((err = get_next_line(ifd, &line)) > 0)
	{
		if (is_empty(line))
		{
			if (!is_label(line))
				if ((err = lstadd(&(tracker->available), line, tracker)))
				{
					free(line);
					return (err);
				}
			ptr = skiplabel(line);
			if (is_empty(ptr))
				if ((err = manage_code(ofd, tracker, ptr)))
				{
					free(line);
					return (err);
				}
		}
		free(line);
	}
	return (err);
}

static int		write_reserved(int ofd, t_track *tracker)
{
	t_list_w	*tmp;
	int			val;

	tmp = tracker->to_find;
	while (tmp)
	{
		val = find_val(tmp, tracker->available);
		lseek(ofd, tmp->w_pos, SEEK_SET);
		push_buf(ofd, val, tmp->w_size);
		clean_buf(ofd);
		tmp = tmp->next;
	}
	lseek(ofd, BOTSIZE_POS, SEEK_SET);
	push_buf(ofd, tracker->w_pos - EXEC_POS, BOTSIZE_SIZE);
	clean_buf(ofd);
	return (0);
}

static int		free_data(t_track *tracker, int err)
{
	t_list_w	*tmp;

	while (tracker->to_find)
	{
		tmp = tracker->to_find;
		if (tmp->content)
			free(tmp->content);
		tracker->to_find = tracker->to_find->next;
		free(tmp);
	}
	while (tracker->available)
	{
		tmp = tracker->available;
		if (tmp->content)
			free(tmp->content);
		tracker->available = tracker->available->next;
		free(tmp);
	}
	return (err);
}

int				write_this_out(int ofd, int ifd)
{
	t_track	tracker;
	int		err;

	ft_bzero(&tracker, sizeof(t_track));
	if ((err = write_header(ofd, ifd, &tracker)))
		return (free_data(&tracker, err));
	if ((err = write_execode(ofd, ifd, &tracker)))
		return (free_data(&tracker, err));
	clean_buf(ofd);
	if ((err = write_reserved(ofd, &tracker)))
		return (free_data(&tracker, err));
	return (free_data(&tracker, err));
}
