/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skholodn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 16:49:56 by skholodn          #+#    #+#             */
/*   Updated: 2017/03/03 16:50:44 by skholodn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char const *s)
{
    if (s)
        return ((int)write(1, s, ft_strlen(s)));
    return (0);
}

t_fl	*init_flags(void)
{
	t_fl	*flag;

	flag = malloc(sizeof(t_fl));
	flag->plus = 0;
	flag->minus = 0;
	flag->hash = 0;
	flag->space = 0;
	flag->zero = 0;
	return (flag);
}

t_e	*env_init(char *buff)
{
	t_e	*env;
	env = (t_e *)malloc(sizeof(t_e));
   env->buf = NULL;
   env->buf = buff;
	env->mod = 0;
	env->width = 0;
	env->precision = -1;
	env->dollar = 0;
	env->spec = 0;
	env->f = init_flags();
	return (env);
}

void    str_cpy(t_e *e, char **fmt)
{
    int     len;

    if (ft_strchr(*fmt, '%') != NULL)
    {
        len = (int)(ft_strchr(*fmt, '%') - *fmt);
        e->buf = ft_strjoin(e->buf, ft_strsub(*fmt, 0, (size_t)len));
        (*fmt) += len;
    }
    else
    {
        len = (int)ft_strlen(*fmt);
        e->buf = ft_strjoin(e->buf, *fmt);
        (*fmt) += len;
    }
}

char    *ft_vsprintf(char *buf, char *fmt, va_list ar)
{
	t_e	*e;

   e = env_init(buf);
   while (*fmt != '\0')
   {
		if (*fmt == '%')
			parse_persent(e, &fmt, ar);
		else
		{
        str_cpy(e, &fmt);
		}
    }
   return (e->buf);
}

int ft_printf(char *fmt, ...)
{
	va_list ar;
	int 	bits_count;
	char *buf;

   g_zero = 0;
   if (fmt == NULL)
		return (-1);
	buf = ft_strnew(0);
	va_start(ar, fmt);
	buf = ft_vsprintf(buf, fmt, ar);
	va_end(ar);
	bits_count = ft_putstr(buf) + g_zero;
   free(buf);
	return (bits_count);
}
