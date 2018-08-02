/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_code.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oleshche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 16:07:01 by oleshche          #+#    #+#             */
/*   Updated: 2018/07/05 16:07:05 by oleshche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oleshche.h"

int			cmd_names(char *cmd_name)
{
	t_ops	info;

	info = find_info(cmd_name);
	if (info.name)
		return (NO_ERR);
	return (1);
}

static int	command_content_in(t_command cmd, int i, t_ops info)
{
	if (info.args[i] == 1 && t_reg_arg(cmd.args[i]))
		return (1);
	else if (info.args[i] == 2 && t_dir_arg(cmd.args[i]))
		return (1);
	else if (info.args[i] == 4 && t_ind_arg(cmd.args[i]))
		return (1);
	else if (info.args[i] == 7 && (t_reg_arg(cmd.args[i])
										|| t_dir_arg(cmd.args[i])
										|| t_ind_arg(cmd.args[i])))
		return (1);
	else if (info.args[i] == 3 && (t_reg_arg(cmd.args[i])
										|| t_dir_arg(cmd.args[i])))
		return (1);
	else if (info.args[i] == 5 && (t_reg_arg(cmd.args[i])
										|| t_ind_arg(cmd.args[i])))
		return (1);
	else if (info.args[i] == 6 && (t_dir_arg(cmd.args[i])
										|| t_ind_arg(cmd.args[i])))
		return (1);
	else if (!cmd.args[i] && !info.args[i])
		return (1);
	return (0);
}

int			command_content(t_command cmd)
{
	t_ops	info;
	int		i;

	i = -1;
	info = find_info(cmd.cmd_name);
	if (!cmd.cmd_name)
		return (1);
	while (++i < 3)
		if (command_content_in(cmd, i, info))
			continue ;
		else
			return (1);
	return (NO_ERR);
}

int			command_check(void)
{
	t_label		*lb;
	t_command	cmd;
	t_list		*tmp;
	t_list		*global;

	global = g_list;
	while (global)
	{
		lb = (t_label*)global->content;
		tmp = lb->commands;
		while (tmp)
		{
			cmd = *((t_command*)tmp->content);
			if (cmd_names(cmd.cmd_name) || command_content(cmd))
				return (1);
			tmp = tmp->next;
		}
		global = global->next;
	}
	return (NO_ERR);
}

int			check_code(void)
{
	if (!g_list || label_name() || command_check())
	{
		ft_lstdel(&g_list, &del_label);
		return (print_err_msg(LEXICAL_ERR, 0, 0));
	}
	ft_lstdel(&g_list, &del_label);
	return (NO_ERR);
}
