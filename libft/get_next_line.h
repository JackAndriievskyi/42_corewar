/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oleshche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 19:30:37 by oleshche          #+#    #+#             */
/*   Updated: 2017/12/21 19:14:08 by oleshche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 10
# define CHECKALLOC(x) if (x == 0) return (-1);

# include "libft.h"
# include "unistd.h"

int		get_next_line(const int fd, char **line);

#endif
