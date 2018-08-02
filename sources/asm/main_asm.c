/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_asm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandriie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 10:57:26 by yandriie          #+#    #+#             */
/*   Updated: 2018/08/01 16:15:05 by yandriie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		check_arg(char *arg)
{
	char	*tmp;

	tmp = ft_strrchr(arg, EXT_CHR);
	if (!tmp || tmp == arg || ft_strcmp(tmp, SRC_EXT))
		return (FILE_ERR);
	return (NO_ERR);
}

static int		check_file(char *arg, int *ifd)
{
	int		fd;
	int		err;

	if ((fd = open(arg, O_RDONLY)) < 0)
		return (print_err_msg(OPEN_ERR, 0, 0));
	if ((err = check_this_out(fd)))
	{
		close(fd);
		return (err);
	}
	*ifd = fd;
	return (NO_ERR);
}

static int		write_file(char *arg, int ifd)
{
	char	output_str[PATH_MAX];
	int		ofd;
	int		len;
	int		err;

	ft_strncpy(output_str, arg, PATH_MAX - 1);
	len = ft_strlen(output_str) - ft_strlen(SRC_EXT);
	ft_strncpy(output_str + len, OUT_EXT, PATH_MAX - len - 1);
	output_str[PATH_MAX - 1] = '\0';
	lseek(ifd, 0, SEEK_SET);
	if ((ofd = open(output_str, O_WRONLY | O_CREAT, CH_MOD)) < 0)
	{
		close(ifd);
		return (print_err_msg(OPEN_ERR, 0, 0));
	}
	if ((err = write_this_out(ofd, ifd)))
	{
		close(ifd);
		close(ofd);
		return (err);
	}
	print_ok_msg(output_str);
	close(ifd);
	close(ofd);
	return (NO_ERR);
}

int				main(int argc, char **argv)
{
	int		err;
	int		ifd;
	int		i;

	err = USAGE_ERR;
	if (argc < MIN_ARGS)
		return (print_err_msg(USAGE_ERR, 0, 0));
	i = 1;
	while (i < argc)
	{
		if (!(err = check_arg(argv[i])))
		{
			if ((err = check_file(argv[i], &ifd)))
				return (err);
			if ((err = write_file(argv[i], ifd)))
				return (err);
		}
		else
		{
			print_err_msg(FILE_ERR, 0, 0);
			ft_putendl(argv[i]);
		}
		i++;
	}
	return (NO_ERR);
}
