/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oleshche.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oleshche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 12:00:00 by oleshche          #+#    #+#             */
/*   Updated: 2018/07/02 12:00:08 by oleshche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OLESHCHE_H
# define OLESHCHE_H

# include "asm.h"
# include "../corewar.h"

int				name_check(char **file);
int				only_spaces(char *str);
void			del_str_arr(char **file);
void			del_line(void *str, size_t size);
int				lst_size(t_list *begin_lst);
int				clear_end(char **file, int i, int j);
int				comment_check(char **file);
int				labels(char **line);
void			skip_name(char **file, int *i);
void			skip_comment(char **file, int *i);
char			**ft_split_whitespaces(char const *s);
int				check_code();
int				t_reg_arg(char *arg);
int				t_dir_arg(char *arg_orig);
int				t_ind_arg(char *arg_orig);
void			spaces_clear(char *str);
int				skip_start(char **file);
t_ops			find_info(char *name);
int				del_args(char **args, int j);
int				comment_line(char *line);
int				next_label(char *line);
void			too_many_args(char **split, int flag, int *j, char **args);
void			parse_labels(char **file, int i);
int				label_name(void);
void			nullify_comment(char *args_str);

t_list	*g_list;

typedef struct	s_label
{
	char	*label;
	t_list	*commands;
}				t_label;

typedef struct	s_command
{
	char	*args[3];
	char	*cmd_name;
}				t_command;

void			del_label(void *label, size_t size);

#endif
