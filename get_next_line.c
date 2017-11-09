/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 14:32:56 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/09 17:04:37 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_next_line.h>

static t_u08	gnl_push(t_list **node, t_i32 const fd)
{
	t_car	buf[BUFF_SIZE];
	ssize_t	r;

	if ((r = read(fd, buf, BUFF_SIZE)) <= 0)
		return (1);
	if (!*node)
		*node = ft_lstnew(buf, (t_usz)r);
	else
	{
		(*node)->next = ft_lstnew(buf, (t_usz)r);
		*node = (*node)->next;
	}
	return (0);
}

static t_usz	gnl_bufferize(t_list **root, t_i32 const fd)
{
	t_list	*node;
	t_car	*s;
	t_usz	n;

	n = 0;
	if (!*root && gnl_push(root, fd))
		return (n);
	s = (*root)->content;
	node = *root;
	while (1)
	{
		if ((t_usz)(s - (t_car *)node->content) >= node->content_size)
		{
			if (gnl_push(&node, fd))
				return (n);
			s = node->content;
		}
		if (!*s || *s == '\n')
		{
			--node->content_size;
			return (n);
		}
		++s;
		++n;
	}
}

t_i32			get_next_line(t_i32 const fd, t_car **line)
{
	static t_list	*cache[256] = {0};
	t_list			*node;
	t_car			*dst;
	t_car			*src;
	t_usz			n;

	if (fd < 0 || !(n = gnl_bufferize(&cache[fd], fd)))
		return (0);
	if (!(*line = malloc((n + 1) * sizeof(t_car))))
		return (-1);
	dst = *line;
	node = cache[fd];
	src = node->content;
	while (n--)
		if (node->content_size--)
			*dst++ = *src++;
		else
		{
			node = node->next;
			src = node->content;
			++n;
		}
	*dst = '\0';
	cache[fd] = node;
	return (1);
}
