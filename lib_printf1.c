/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_printf1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skholodn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/04 15:24:17 by skholodn          #+#    #+#             */
/*   Updated: 2017/03/04 15:24:22 by skholodn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char    *ft_charjoin(char *s1, char c)
{
    size_t	ls1;
    size_t	i;
    char	*strnew;

    strnew = NULL;
    if (s1 && c)
    {
        i = -1;
        ls1 = ft_strlen(s1);
        if (!(strnew = ft_strnew(ls1 + 1)))
            return (NULL);
        while (s1[++i])
            strnew[i] = s1[i];
        strnew[i] = c;
        return (strnew);
    }
    return (strnew);
}
