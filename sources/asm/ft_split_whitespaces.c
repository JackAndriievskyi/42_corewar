/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oleshche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 18:51:05 by oleshche          #+#    #+#             */
/*   Updated: 2017/11/06 18:51:06 by oleshche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oleshche.h"

static int		word_len(const char *s, int index)
{
	int			len;

	len = 0;
	while (!ft_strchr(" \t\n\f\v", s[index]) && s[index] != '\0')
	{
		len++;
		index++;
	}
	return (len);
}

static int		count_words(const char *s)
{
	int			counter;
	int			i;

	i = 0;
	counter = 0;
	while (ft_strchr(" \t\n\f\v", s[i]) && s[i] != '\0')
		i++;
	while (s[i] != '\0')
	{
		if (!ft_strchr(" \t\n\f\v", s[i]) &&
			(ft_strchr(" \t\n\f\v", s[i + 1]) || s[i + 1] == '\0'))
			counter++;
		i++;
	}
	return (counter);
}

static void		ft_strndel(char ***s, int j)
{
	int i;

	i = 0;
	while (i < j)
		ft_strdel(&s[0][i++]);
	free(*s);
	*s = NULL;
}

char			**ft_split_whitespaces(char const *s)
{
	char		**res;
	int			i;
	int			j;
	int			counter;

	if (!s)
		return (NULL);
	counter = count_words(s);
	if (!(res = (char **)malloc(sizeof(char *) * (counter + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] != '\0' && j < counter && res)
	{
		while (ft_strchr(" \t\n\f\v", s[i]))
			i++;
		res[j] = ft_strsub(s, (size_t)i, (size_t)word_len(s, i));
		if (!(res[j++]))
			ft_strndel(&res, j + 1);
		i += word_len(s, i);
	}
	if (!res)
		return (NULL);
	res[j] = 0;
	return (res);
}
