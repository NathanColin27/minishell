/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_empty.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 11:45:10 by adorigo           #+#    #+#             */
/*   Updated: 2021/01/04 15:00:24 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

static int	is_sep(char c, char sep)
{
	if (c == sep)
		return (1);
	return (0);
}

static int	count_words(char const *str, char sep)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (!is_sep(str[i], sep) && (i == 0 || is_sep(str[i - 1], sep)))
			count++;
		i++;
	}
	return (count);
}

static char	*malloc_word(char const *str, char sep)
{
	char	*word;
	int		word_len;
	int		i;

	word_len = 0;
	i = 0;
	while (str[word_len] && !is_sep(str[word_len], sep))
		word_len++;
	if (!(word = (char *)calloc((word_len + 1), sizeof(char))))
		return (0);
	while (str[i] && !is_sep(str[i], sep))
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void	*free_tab(char **tab, int i)
{
	while (i >= 0)
	{
		if (tab[i])
			free(tab[i]);
		i--;
	}
	free(tab);
	return (NULL);
}

char		**ft_split_empty(char const *str, char sep)
{
	char	**tab;
	int		i;
	int		j;
	char	buff[LINE_MAX];

	j = 0;
	i = -1;
	if (!str)
		return (0);
	bzero(buff, 4096);
	while (str[++i])
	{
		if (is_sep(str[i], sep) && (((i != 0 && is_sep(str[i-1], sep)) || i == 0)))
			buff[j++] = -1;
		buff[j++] = str[i];
	}
	if (!(tab = (char **)malloc(sizeof(char *) * (count_words(buff, sep) + 1))))
		return (0);
	i = 0;
	j = 0;
	while (buff[j])
	{
		while (buff[j] && is_sep(buff[j], sep))
			j++;
		if (buff[j] && (!is_sep(buff[j], sep)))
		{
			if (!(tab[i] = malloc_word(&buff[j], sep)))
				return (free_tab(tab, i));
			i++;
			while (buff[j] && !is_sep(buff[j], sep))
				j++;
		}
	}
	tab[i] = NULL;
	return (tab);
}
