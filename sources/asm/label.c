/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oleshche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 15:16:10 by oleshche          #+#    #+#             */
/*   Updated: 2018/07/02 15:16:14 by oleshche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oleshche.h"

void	the_same_str(char **curr_split, t_list **cmd_list, char *line)
{
	t_command	cmd;
	int			j;
	char		**spl;
	int			flag;

	j = 0;
	flag = 1;
	cmd.cmd_name = ft_strdup(curr_split[1]);
	spl = ft_strsplit(ft_strstr(line + ft_strlen(curr_split[0]),
	cmd.cmd_name) + ft_strlen(cmd.cmd_name), SEPARATOR_CHAR);
	while (j < 3 && spl[j])
	{
		cmd.args[j] = ft_strtrim(spl[j]);
		if (ft_strchr(cmd.args[j++], COMMENT_CHAR) && flag--)
		{
			nullify_comment(cmd.args[j - 1]);
			break ;
		}
	}
	too_many_args(spl, flag, &j, cmd.args);
	while (j < 3)
		cmd.args[j++] = NULL;
	ft_lstaddback(cmd_list, ft_lstnew(&cmd, sizeof(t_command)));
	del_str_arr(spl);
}

void	parse_args(t_command *cmd, char *line)
{
	char	**spl;
	int		j;
	int		flag;

	j = 0;
	flag = 1;
	spl = ft_strsplit(ft_strstr(line, cmd->cmd_name)
				+ ft_strlen(cmd->cmd_name), SEPARATOR_CHAR);
	while (j < 3 && spl[j])
	{
		cmd->args[j] = ft_strtrim(spl[j]);
		if (ft_strchr(cmd->args[j++], COMMENT_CHAR) && flag--)
		{
			nullify_comment(cmd->args[j - 1]);
			break ;
		}
	}
	too_many_args(spl, flag, &j, cmd->args);
	while (j < 3)
		cmd->args[j++] = NULL;
	del_str_arr(spl);
}

t_list	*parse_commands(char **file, char **curr_split, int *i)
{
	char		**split;
	t_command	cmd_line;
	t_list		*cmd_list;

	cmd_list = NULL;
	if (curr_split[1])
		the_same_str(curr_split, &cmd_list, file[*i]);
	while (!next_label(file[(*i + 1)]) && file[++(*i)])
	{
		if (only_spaces(file[*i]) || comment_line(file[*i]))
			continue ;
		split = ft_split_whitespaces(file[*i]);
		cmd_line.cmd_name = ft_strdup(split[0]);
		parse_args(&cmd_line, file[*i]);
		ft_lstaddback(&cmd_list, ft_lstnew(&cmd_line, sizeof(t_command)));
		del_str_arr(split);
	}
	return (cmd_list);
}

void	parse_main(char **file, int *i)
{
	t_label		lb;
	char		**split;
	t_list		*cmd_list;
	t_command	cmd_line;

	lb.label = NULL;
	cmd_list = NULL;
	*i -= 1;
	while (!next_label(file[(++(*i))]) && file[(*i)])
	{
		if (only_spaces(file[*i]) || comment_line(file[*i]))
			continue ;
		split = ft_split_whitespaces(file[*i]);
		cmd_line.cmd_name = ft_strdup(split[0]);
		parse_args(&cmd_line, file[(*i)]);
		ft_lstaddback(&cmd_list, ft_lstnew(&cmd_line, sizeof(t_command)));
		del_str_arr(split);
	}
	lb.commands = cmd_list;
	ft_lstaddback(&g_list, ft_lstnew(&lb, sizeof(t_label)));
}

void	parse_labels(char **file, int i)
{
	char	**split;
	t_label	label;

	g_list = NULL;
	while (file[i])
	{
		if (only_spaces(file[i]))
			continue ;
		split = ft_split_whitespaces(file[i]);
		if (!g_list && find_info(split[0]).name)
		{
			parse_main(file, &i);
			del_str_arr(split);
			continue ;
		}
		label.label = ft_strdup(split[0]);
		label.commands = parse_commands(file, split, &i);
		ft_lstaddback(&g_list, ft_lstnew(&label, sizeof(t_label)));
		del_str_arr(split);
		if (!file[i])
			break ;
		i++;
	}
}
