/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brackets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 14:02:19 by alessandro        #+#    #+#             */
/*   Updated: 2020/11/11 17:51:34 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_bracket_removal(t_cmd **cmd)
{
	char	**new_argv;
	char	*tmp;
	char	*tmp2;
	int		i;
	int		j;

	i = 0;
	tmp = NULL;
	while((*cmd)->argv[i])
		i++;
	if (!(new_argv = malloc(sizeof(char *) * i + 1)))
		return(-1);
	i = 0;
	while((*cmd)->argv[i])
	{
		j = 0;
		while((*cmd)->argv[i][j])
		{
			if ((*cmd)->argv[i][j] == '\"' || (*cmd)->argv[i][j] == '\'')
			{
				if (tmp == NULL)
					tmp = ft_strndup((*cmd)->argv[i], j);
				printf("%d\n", j);
				j = ft_brackets((*cmd)->argv[i], j);
				printf("%d\n", j);
				printf("start = %lu\n lenght = %ld\n", j - (ft_strlen((*cmd)->argv[i]) - j), (ft_strlen((*cmd)->argv[i]) - j));
				tmp2 = ft_substr((*cmd)->argv[i], j - ft_strlen((*cmd)->argv[i]) - j, (ft_strlen((*cmd)->argv[i]) - j));
				printf("tmp = %s | tmp2 = %s\n", tmp, tmp2);
				printf("len tmp = %zu\nlen tmp2 = %zu\n",ft_strlen(tmp), ft_strlen(tmp2));
				tmp = ft_strjoin_free(tmp, tmp2);
				free(tmp2);
			}
			j++;
		}
		if (!tmp)
			new_argv[i] = ft_strdup((*cmd)->argv[i]);
		else
			new_argv[i] = ft_strdup(tmp);
		if (tmp)
			free(tmp);
		i++;
	}
	new_argv[i] = NULL;
	int z = 0;
	while (new_argv[z])
	{
		printf("new_argv = %s\n", new_argv[z]);
		z++;
	}
	ft_free_array((*cmd)->argv);
	(*cmd)->argv = new_argv;
	return (1);
}