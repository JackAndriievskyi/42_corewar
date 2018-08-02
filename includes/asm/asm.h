/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandriie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 10:58:55 by yandriie          #+#    #+#             */
/*   Updated: 2018/08/01 16:00:41 by yandriie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "../corewar.h"
# include "../../libft/libft.h"
# include <limits.h>

# define NO_ERR 0
# define MALLOC_ERR 1
# define USAGE_ERR 2
# define OPEN_ERR 3
# define FILE_ERR 4
# define SYNTAX_ERR 5
# define NAME_TOO_LONG 6
# define COMM_TOO_LONG 7
# define LEXICAL_ERR 8

# define USAGE_ERR_MSG "Usage: ./asm <sourcefile.s ...>"
# define MALLOC_ERR_MSG "/tsome of stdlib's function has failed, aborting..."
# define OPEN_ERR_MSG "Cannot open file"
# define FILE_ERR_MSG "WRONG FILE:"
# define SYNTAX_ERR_MSG "Syntax error"
# define NAME_TOO_LONG_MSG "Champion name too long (Max length 128)"
# define COMM_TOO_LONG_MSG "Comment too long (Max length 2048)"
# define LEXICAL_ERR_MSG "Lexical error"

# define FINAL_OK_MSG "Writing output program to "

# define MIN_ARGS 2
# define EXT_CHR '.'
# define SRC_EXT ".s"
# define OUT_EXT ".cor"
# define CH_MOD 0600

int				print_err_msg(int err, int arg1, int arg2);
void			print_ok_msg(char *msg);
int				check_this_out(int fd);
int				write_this_out(int ofd, int ifd);

#endif
