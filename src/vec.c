/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irsander <irsander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:14:36 by irsander          #+#    #+#             */
/*   Updated: 2024/06/04 12:10:48 by irsander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

bool	vec_resize(t_vec *vec)
{
	char	*tmp;

	tmp = malloc(sizeof(char) * (vec->alloc_size * 2));
	if (!tmp)
		return (false);
	vec->alloc_size *= 2;
	ft_memcpy(tmp, vec->data, vec->length);
	free(vec->data);
	vec->data = tmp;
	return (true);
}

bool	vec_push(t_vec *vec, char c)
{
	if (vec->length == vec->alloc_size)
		vec_resize(vec);
	vec->data[vec->length] = c;
	vec->length++;
	return (true);
}

void	vec_init(t_vec *vec, int size)
{
	vec->data = malloc(sizeof(char) * size);
	vec->length = 0;
	vec->alloc_size = size;
}
