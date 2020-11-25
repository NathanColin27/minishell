/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 18:09:34 by adorigo           #+#    #+#             */
/*   Updated: 2020/11/25 15:42:39 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Joins *char 's1' and *char 's2' with a character 'del' between the two.
*/

char *ft_strjoin_delimiter(char *s1, char *s2, char del)
{
	char *str;
	char *to_free;
	int total;
	int i;

	i = 0;
	to_free = s1;
	if (!s1 || !s2)
		return (NULL);
	total = ft_strlen(s1) + ft_strlen(s2) + 2;
	if (!(str = (char *)malloc(total * sizeof(char))))
		return (NULL);
	while (*s1)
		str[i++] = *s1++;
	str[i++] = del;
	while (*s2)
		str[i++] = *s2++;
	str[i] = '\0';
	return (str);
}

int ft_count_arg(char **arg)
{
	int i;

	i = 0;
	while (arg[i])
		i++;
	return (i);
}

t_cmd *ft_last_cmd(t_cmd *cmd)
{
	t_cmd *last;

	last = cmd;
	while (last->next)
		last = last->next;
	return (last);
}

int ft_skip_quotes(char *str, int i)
{
	if (str[i] == '\'')
	{
		i++;
		while (str[i] != '\'')
			i++;
	}
	return (i);
}

static long check_lvlneg(unsigned long nbr, int is_neg)
{
	if (!is_neg)
		return (nbr);
	else
		return (LONG_MAX - nbr + 1);
}

static int checker(const char *str)
{
	int is_negative;

	is_negative = 0;
	if (str[0] == '-' || str[0] == '+')
	{
		if (str[0] == '-')
			is_negative = 1;
	}
	return (is_negative);
}

static int check_sign(char c)
{
	if (c == '+' || c == '-')
		return (1);
	return (0);
}

long ft_atoi_pos(const char *str)
{
	unsigned long nb;
	int i;
	int is_negative;
	int is_sign;

	is_negative = checker(str);
	is_sign = check_sign(str[0]);
	i = is_sign;
	nb = 0;
	if (ft_strlen(str) > (size_t)(19 + is_sign))
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (nb > (unsigned long long)LONG_MAX)
			return ((long)0);
		nb *= 10;
		nb += str[i] - '0';
		i++;
	}
	if (nb > (unsigned long long)LONG_MAX)
		return ((long)0);
	if (nb >= (unsigned long long)INT_MAX - 1 &&
		nb <= (unsigned long long)LONG_MAX)
		return (check_lvlneg(nb, is_negative));
	return ((long)nb);
}

void ft_free_node(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env);
}

char *ft_strtrim_integral(char const *s1, char const set)
{
	char **tab;
	char *str_finale;
	int i;

	i = 0;

	tab = ft_split(s1, set);
	str_finale = ft_strdup("");
	while (tab[i])
	{
		if (!(str_finale = ft_strjoin_free(str_finale, tab[i])))
		{
			ft_free_array(tab);
			return (NULL);
		}
		i++;
	}
	ft_free_array(tab);
	return (str_finale);
}

int ft_backslash_counter(char *str, int i)
{
	int counter;

	counter = 0;
	while (i >= 0 && str[i] == '\\')
	{
		counter++;
		i--;
	}
	return (counter % 2);
}

int ft_isascii_except(int c)
{
	if (c >= ' ' && c <= '~' && c != '$' && c != '"' && c != '\\')
		return (0);
	return (1);
}

char *remove_char(char *str, char c)
{
	char *new;
	int i;
	int j;
	int l;

	new = ft_strnew(ft_strlen(str));
	i = 0;
	j = 0;
	l = ft_strlen(str);
	while (i < l)
	{
		if (str[i] != c)
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';
	return (new);
}

int free_str_ret(char *str)
{
	free(str);
	return (1);
}