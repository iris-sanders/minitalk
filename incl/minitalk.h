/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irsander <irsander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:32:39 by irsander          #+#    #+#             */
/*   Updated: 2024/05/28 15:12:56 by irsander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "libft.h"
# include "ft_printf.h"
# include <signal.h>
# include <unistd.h>
# include <sys/types.h>
#include <stdbool.h>

/**
 * @brief Struct for a small vector
 * 
 * @param data The actual string
 * @param length The total amount of chars inserted
 * @param alloc_size The total amount of memory that can be filled. 
 */
typedef struct s_vec {
    char *data;
    int length;
    int alloc_size;
} t_vec;

bool vec_resize(t_vec *vec);
bool vec_push(t_vec *vec, char c);
void vec_init(t_vec *vec, int size);

#endif