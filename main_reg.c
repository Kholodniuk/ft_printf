/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_reg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skholodn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 19:25:09 by skholodn          #+#    #+#             */
/*   Updated: 2017/03/15 23:58:05 by skholodn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#include <stdio.h>
#include <stddef.h>
#include <locale.h>
#include <limits.h>
#include <errno.h>
#include <unistd.h>

int		main(void)
{
	//	   printf("%3$daaa%djjj %1$d\n", 1, 2, 3, 4, 5);
	//	ft_printf("%3$daaa%djjj %1$d\n", 1, 2, 3, 4, 5);
	write(-1, "FUCK\n", 5);
	return (0);
}
