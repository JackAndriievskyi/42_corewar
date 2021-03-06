/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmiachko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 12:43:17 by vmiachko          #+#    #+#             */
/*   Updated: 2018/07/27 16:14:46 by vmiachko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "parsing.h"

int					check_if_file(int fd, t_bot *tmp)
{
	char			buf[1];

	if (read(fd, &buf, 0) < 0)
	{
		ft_printf(RED"Error: File %s is too ", tmp->filename);
		ft_printf("small to be a champion\n"RESET);
		return (0);
	}
	if (!ft_strstr(tmp->filename, ".cor"))
	{
		ft_printf(RED"Wrong file. Name of file should end with .cor!\n"RESET);
		return (0);
	}
	return (1);
}

int					check_sum(int fd, unsigned int val)
{
	unsigned int	sum;
	unsigned char	magic_header[8];
	int				r;

	r = (int)read(fd, &magic_header, 4);
	if (r < 4)
		return (0);
	magic_header[r] = '\0';
	sum = 0;
	sum += magic_header[3] +
		(magic_header[2] << 8) +
			(magic_header[1] << 16) +
				(magic_header[0] << 24);
	if (sum != val)
	{
		ft_printf(RED"Wrong magic header or size.\n"RESET);
		return (0);
	}
	return (1);
}

int					fill_bot(t_union *un)
{
	t_bot			*tmp;
	int				fd;

	tmp = un->bot;
	while (tmp)
	{
		fd = open(tmp->filename, O_RDONLY);
		if (!check_if_file(fd, tmp))
			return (0);
		if (!check_sum(fd, COREWAR_EXEC_MAGIC) || !get_bot_name(fd, &tmp) ||
				!check_sum(fd, 0) || !get_bot_size(fd, &tmp) ||
				!get_bot_comment(fd, &tmp) || !check_sum(fd, 0) ||
				!get_bot_code(fd, &tmp) || !check_size_is_true(*tmp))
		{
			close(fd);
			return (0);
		}
		close(fd);
		tmp = tmp->next;
	}
	return (1);
}

int					parse_bot(t_union *un)
{
	int				r;

	while (!(r = set_bot_id(un, NULL, NULL)))
		set_bot_id(un, NULL, NULL);
	if (r == -1)
		return (-1);
	else if (!fill_bot(un))
	{
		bot_clear_list(un->bot);
		return (0);
	}
	return (1);
}
