/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:52:57 by alucas-           #+#    #+#             */
/*   Updated: 2017/11/08 15:09:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

inline t_i32	ft_strcmp(t_car const *s1, t_car const *s2)
{
	while (((t_u08)*s1 == (t_u08)*s2) && *s1)
	{
		++s1;
		++s2;
	}
	return (*(t_u08 *)s1 - *(t_u08 *)s2);
}
