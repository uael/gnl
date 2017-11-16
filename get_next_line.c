/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 14:32:56 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/14 18:15:41 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(int const fd, char **line)
{
	static t_dstr	c[INT32_MAX];
	char			b[BUFF_SIZE + 1];
	ssize_t			i;
	char			*eol;

	eol = NULL;
	if (!line || fd < 0)
		return (-1);
	while ((!c[fd].len || (eol || !(eol = ft_strchr(c[fd].buf, '\n')))))
		if ((i = read(fd, b, BUFF_SIZE)) == 0)
			break ;
		else if (i == -1 || !(eol = ft_dstr_pushnc(c + fd, b, (size_t)i)))
			return (-1);
		else if ((eol = ft_strchr(eol, '\n')))
			break ;
	if (!(i = eol ? (eol - c[fd].buf + 1) : (ssize_t)c[fd].len))
		return (0);
	if (!(*line = malloc((size_t)(i + (eol ? 1 : 0)) * sizeof(char))))
		return (-1);
	(*line)[ft_dstr_shiftn(c + fd, (size_t)i, *line) - (eol ? 1 : 0)] = '\0';
	return (1);
}
