/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_write.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yandriie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 08:50:29 by yandriie          #+#    #+#             */
/*   Updated: 2018/07/25 13:22:17 by yandriie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_WRITE_H
# define ASM_WRITE_H

# include "../../libft/libft.h"
# include "../corewar.h"

typedef struct	s_list_w {
	void			*content;
	int				w_pos;
	int				s_pos;
	int				w_size;
	struct s_list_w	*next;
}				t_list_w;

typedef struct	s_track
{
	int			w_pos;
	int			s_pos;
	int			codage;
	int			val;
	int			size;
	t_header	header;
	t_ops		op;
	t_list_w	*to_find;
	t_list_w	*available;
}				t_track;

# define BLANK_SPACE 0

# define BOTSIZE_POS 136
# define EXEC_POS 2192

# define MAGIC_SIZE 4
# define BLANK_SPACE_SIZE 4
# define BOTSIZE_SIZE 4

# define OP_CODE_SIZE 1
# define CODAGE_SIZE 1
# define IND_CODE_SIZE 2
# define REG_CODE_SIZE 1

# define ASM_BUFF_SIZE 32

# define OPS_NUMBER 16

# define DQUOTE_CHR '\"'

typedef union	u_val
{
	int		ival;
	char	bval[4];
}				t_val;

int				push_buf(int ofd, int val, int size);
void			clean_buf(int ofd);
int				lstadd(t_list_w **lst, char *str, t_track *tr);
int				manage_code(int ofd, t_track *tracker, char *src);
int				is_empty(char *str);
int				is_label(char *str);
char			*skiplabel(char *str);
char			*skip(char *str);
int				find_val(t_list_w *to_find, t_list_w *available);
int				is_name(char *str);
int				is_comment(char *str);
int				get_text(char *src, int ifd, char *dst, int f);
void			push_header(int ofd, t_track *tracker);

#endif
